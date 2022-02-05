#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "plan.h"
#include "strahl.h"
#include "kugel.h"
#include "ebene.h"
#include "kamera.h"
#include "szene.h"
#include "material.h"

    // ------- Helfer - Funktionen -------
	float cosBeta(TVektor a, TVektor b){
        // gibt einen Wert zwischen [0, 1] zurueck
        // als Mass fuer den Winkel zwischen zwei Vektoren
        return std::max(0.0, ((a*b)/(sqrt(a*a)*sqrt(b*b))) );
    }

    float map(float x, float start1, float stop1, float start2, float stop2){
        return(start2+((x-start1)/(stop1-start1))*(stop2-start2));
    }

    TColor hintergrundFarbe(float x, float start, float stop){
        int r = (int)(map(x,start,stop,255,200)*100.0/255);          // 20
        int g = (int)(map(x,start,stop,255,200)*100.0/255);         // 100
        int b = (int)(map(x,start,stop,255,200)*100.0/255);         // 200
        return RGBSkala(r,g,b);
    }

    // ------- berechneFarbe - Funktion -------

    TVektor berechneFarbe(Szene szene, Strahl s, int iteration){
        // Abbruchbedingung Rekursion: wenn maximale Anzahl Strahlen erreicht -> keinen Farbbeitrag mehr ermitteln.
        if (iteration == 0) return TVektor(0,0,0);

        // Strahl mit der Szene schneiden und vorderstes Schnittobjekt mit Index i ermitteln.
        float abstand;
        float abstandMin  = std::numeric_limits<float>::infinity();
        int gewinner = -1;
        for(int i=0; i<szene.anzObjekte; i++){
            s = szene.objekte[i]->schnitt(s);
            if ((s.entfernung > 0)&&(s.entfernung < abstandMin)){
                abstandMin=s.entfernung;
                gewinner = i;
            }
        }

        // Wenn ein Objekt geschnitten wurde, den Farbbeitrag nach Shading-Modellen ermitteln
        if (gewinner >=0){

            // Schnittinformationen in s_treffer speichern.
            Strahl s_treffer = szene.objekte[gewinner]->schnitt(s);

        // ### PUNKTLICHT-SHADER ###

        // ### LAMBERTIAN SHADING ###
            TVektor lambertian;
            float beleuchtung = 0.1;
            Strahl lichtstrahl;

            for(int i=0; i<szene.anzLichter; i++){
                // ... -> Lichtstrahl von Objekt zur Lichtquelle berechnen
                lichtstrahl.richtung = szene.lichter[i]->position - s_treffer.schnittpunkt;
                EinheitsVektor(lichtstrahl.richtung);
                lichtstrahl.ursprung = s_treffer.schnittpunkt + 0.01*lichtstrahl.richtung;

                // Pruefen, ob Objekte im Weg sind
                bool verdeckt = false;
                for(int j=0; j<szene.anzObjekte; j++){
                    // den Lichtstrahl mit allen Objekten schneiden und Schnittinformationen speichern
                    lichtstrahl = szene.objekte[j]->schnitt(lichtstrahl);
                    if (lichtstrahl.entfernung > 0){
                        verdeckt = true;
                    }
                }

                // wenn die aktuell untersuchte Lichtquelle das nahste Objekt ist, dann Beleuchtung ermitteln
                if (!verdeckt) {
                    beleuchtung += cosBeta(lichtstrahl.richtung, s_treffer.normale);
                }
            }

            int r = int(GetRValue(szene.objekte[gewinner]->material.farbe));
            int g = int(GetGValue(szene.objekte[gewinner]->material.farbe));
            int b = int(GetBValue(szene.objekte[gewinner]->material.farbe));
            if (beleuchtung > 1){beleuchtung = 1;}
            lambertian = TVektor(r,g,b) * beleuchtung;


            // ### REFLECTION SHADING ###
            TVektor reflection(0,0,0);
            if (szene.objekte[gewinner]->material.reflekt > 0){
                // Strahl reflektieren (Einfallswinkel = Ausfallswinkel).
                Strahl reflektionsStrahl;
                reflektionsStrahl.richtung = s_treffer.richtung - 2 * (s_treffer.richtung * s_treffer.normale) * s_treffer.normale;
                EinheitsVektor(reflektionsStrahl.richtung);
                reflektionsStrahl.ursprung = s_treffer.schnittpunkt +0.01*reflektionsStrahl.richtung;
                // Farbe rekursiv mit reflektiertem Strahl berechnen:
                reflection = berechneFarbe(szene,reflektionsStrahl,iteration-1);
            }


            // ### FARBBEITRAEGE MISCHEN ###
            float ref_anteil = szene.objekte[gewinner]->material.reflekt;
            return (reflection*ref_anteil + lambertian*(1.0-ref_anteil));
        }

        // Wenn kein Objekt geschnitten wurde, Hintergrundfarbe zurueckgeben.
        TColor hintergrund = hintergrundFarbe(s.richtung[2],-1,1);
        return TVektor(GetRValue(hintergrund),GetGValue(hintergrund),GetBValue(hintergrund));
    }


    TColor farbeMischen(TColor c1, TColor c2, float anteil){
        // mischt zwei Farben c1 und c2
        // float anteil gibt den Anteil von c1 an, zwischen 0 und 1
        int r = int((anteil*GetRValue(c1)+(1-anteil)*GetRValue(c2)));
        int g = int((anteil*GetGValue(c1)+(1-anteil)*GetGValue(c2)));
        int b = int((anteil*GetBValue(c1)+(1-anteil)*GetBValue(c2)));
    return RGB(r,g,b);
    }
	
#endif