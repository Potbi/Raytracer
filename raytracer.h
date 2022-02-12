#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "plan.h"
#include "strahl.h"
#include "kugel.h"
#include "ebene.h"
#include "dreieck.h"
#include "kamera.h"
#include "szene.h"
#include "material.h"

//--------------------------------- Konstanten ----------------------------------

const float VERSATZ = 1.0e-5;
const float UNENDL = std::numeric_limits<float>::infinity();

//----------------------------- Helfer-Funktionen -------------------------------

float cosBeta(TVektor a, TVektor b){
    // Gibt den cos des Winkels zwischen Vektoren a, b zurueck,
    // return-Wert zwischen 0 (parallel) und 1 (orthogonal).
    return std::max(0.0, ((a*b)/(sqrt(a*a)*sqrt(b*b))) );
}

float interp(float x, float start1, float stop1, float start2, float stop2){
    // Bildet x vom Intervall [start1, stop1] auf [start2, stop2] ab.
    return(start2+((x-start1)/(stop1-start1))*(stop2-start2));
}

TVektor hintergrundFarbe(float x, float start, float stop){
    // Gibt fuer ein x aus dem Intervall [start, stop] die Farbe
    // aus einer Farbskala zurueck.
    int r = interp(x,start,stop,20,200);
    int g = interp(x,start,stop,100,200);
    int b = interp(x,start,stop,200,200);
    return TVektor(r,g,b);
}

TVektor TColor2TVektor(TColor farbe){
    // Konvertiert TColor in TVektor.
    int r = int(GetRValue(farbe));
    int g = int(GetGValue(farbe));
    int b = int(GetBValue(farbe));
    return TVektor(r,g,b);
}

TVektor clip(TVektor a){
    // Begrenzt die Eintraege eines TVektors auf maximal 255.
    for (int i=0; i<3; i++){
        a[i] = std::min(255,a[i]);
    }
    return a;
}

//--------------------- SHADING (berechneFarbe - Funktion) ----------------------

TVektor berechneFarbe(Szene szene, Strahl s, int iteration){
    // Berechnet fuer einen uebergebenen Strahl und eine Szene
    // rekursiv den Farbbeitrag anhand der vom Strahl geschnittenen
    // Primitive mit drei Shading-Modellen.

    // Abbruch der Rekursion (maximale Iterationen erreicht).
    if (iteration == 0) return TVektor(0,0,0);

    // Alle Primitive der Szene auf Schnittpunkte mit dem Strahl
    // ueberpruefen, ggfs. vorderstes Primitiv ermitteln und
    // den Index in gewinner speichern.
    float abstandMin  = UNENDL;
    int gewinner = -1;
    for(int i=0; i<szene.anzObjekte; i++){
        s = szene.objekte[i]->schnitt(s);
        if ((s.entfernung > 0) && (s.entfernung < abstandMin)){
            abstandMin=s.entfernung;
            gewinner = i;
        }
    }

    //--------------------------- (1) Punktlicht-Shader -------------------------
    float entfernung;
    TVektor lichtShader(0,0,0);
    float beitrag;

    // Ermittle Leuchtbeitrag von allen nicht-verdeckten Punktlichtern.
    for(int i=0; i<szene.anzLichter; i++){
        s = szene.lichter[i]->schnitt(s);
        if ((s.entfernung > 0) && (s.entfernung < abstandMin)){
            beitrag = 1 - sqrt(1-pow((cosBeta((-1)*s.richtung,s.normale)),2));
            lichtShader += beitrag * TVektor(255,255,255);
        }
    }

    // Wenn kein Primitiv geschnitten wurde, Hintergrundfarbe zurueckgeben.
    if (gewinner == -1){
        // Blau-Wert zurueckgeben, je nach z-Wert des Strahls.
        return clip(hintergrundFarbe(s.richtung[2],-1,1) + lichtShader);
    }

    //---------------------------- (2)  Primitiv-Shader -------------------------
    // Wenn Primitive geschnitten wurden, dann Lambertian-/Reflektionsshading.
    // Schnittinformationen (Entfernung, Normale, Schnittpunkt) fuer das
    // vorderste Primitiv im Srahl treffer speichern.
    Strahl treffer = szene.objekte[gewinner]->schnitt(s);

    //---------------------------- (2a) Lambertian ------------------------------
    TVektor lambertian;
    float beleuchtung = 0.15;
    Strahl lichtstrahl;

    for(int i=0; i<szene.anzLichter; i++){

        // Vom Schnittpunkt aus zu jeder Lichtquelle einen Lichtstrahl berechnen.
        lichtstrahl.richtung = szene.lichter[i]->position - treffer.schnittpunkt;
        EinheitsVektor(lichtstrahl.richtung);
        lichtstrahl.ursprung = treffer.schnittpunkt + VERSATZ*lichtstrahl.richtung;

        // Ueberpruefen, ob sich Primitive zwischen Schnittpunkt
        // und Lichtquelle befinden.
        bool verdeckt = false;
        float abstand = Norm(szene.lichter[i]->position - treffer.schnittpunkt);
        for(int j=0; j<szene.anzObjekte; j++){
            lichtstrahl = szene.objekte[j]->schnitt(lichtstrahl);
            if ((lichtstrahl.entfernung > 0) && (lichtstrahl.entfernung < abstand)){
                verdeckt = true;
            }
        }
        // Wenn Lichtquelle nicht verdeckt, Beleuchtungsbeitrag ermitteln.
        if (!verdeckt) {
            beleuchtung += cosBeta(lichtstrahl.richtung, treffer.normale);
        }
    }

    // Ermitteln der Farbe aus Beleuchtung und Materialfarbe des Primitivs.
    if (beleuchtung > 1) { beleuchtung = 1; }
    lambertian = TColor2TVektor(szene.objekte[gewinner]->material.farbe) * beleuchtung;


    //---------------------------- (2b) Reflektion ------------------------------
    TVektor reflektion(0,0,0);
    if (szene.objekte[gewinner]->material.reflekt > 0){

        // Reflektierten Strahl berechnen (Einfallswinkel = Ausfallswinkel).
        Strahl reflektionsStrahl;
        reflektionsStrahl.richtung = treffer.richtung - 2 * (treffer.richtung * treffer.normale) * treffer.normale;
        EinheitsVektor(reflektionsStrahl.richtung);
        reflektionsStrahl.ursprung = treffer.schnittpunkt + VERSATZ*reflektionsStrahl.richtung;
        
        // Farbe rekursiv mit reflektiertem Strahl berechnen:
        reflektion = berechneFarbe(szene,reflektionsStrahl,iteration-1);
    }

    //-------------------- Farbbeitraege mischen und zurueckgeben ----------------
    float ref_anteil = szene.objekte[gewinner]->material.reflekt;
    return clip(reflektion*ref_anteil + lambertian*(1.0-ref_anteil) + lichtShader);
}

#endif