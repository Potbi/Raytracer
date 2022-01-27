//====================================================================
// Simulation dynamischer Systeme mit PLAN
//====================================================================
// Projektbeschreibung:
//
//====================================================================
#include <vcl.h>
#pragma hdrstop
#include "Plan.h"
#include <iostream>

#include "strahl.h"
#include "kugel.h"
#include "kamera.h"
#include "szene.h"

Kamera* kamera;
Szene* szene;

class TUser : public TPlan {

    float parralelitaetZweiVektoren(TVektor a, TVektor b){
                // winkel zwischen Vektoren von 0-1
                // 1= Parralel 0= Orthogonal
                float top;
                float bottom;
                top = a*b;
                bottom = Norm(a)*Norm(b);
                float temp = top/bottom;
                return sqrt(temp*temp);
    }

    TVektor berechneFarbe(Szene szene, Strahl s, int iteration){
        // Abbruchbedingung Rekursion: wenn maximale Anzahl Strahlen erreicht -> keinen Farbbeitrag mehr ermitteln.
        if (iteration == 0) return Schwarz;
        Strahl s_treffer;

        // Strahl mit der Szene schneiden und vorderstes Schnittobjekt mit Index i ermitteln.
        float abstand;
        float abstandMin  = std::numeric_limits<float>::infinity();
        int gewinner = -1;
        for(int i=0; i<szene.anzObjekte; i++){
            s = szene.objekte[i]->schnitt(s);
            if ((s.entfernung > 0)&&(s.entfernung < abstandMin)){
                abstandMin=s.entfernung;
                s_treffer = s; // ACHTUNG
                gewinner = i;
            }
        }
        // Wenn kein Objekt getroffen wurde, Hintergrundfarbe der Szene zur�ckgeben.
        TVektor lambertian = szene.hintergrund;
        TVektor reflection = NULL;

        // Wenn ein Objekt geschnitten wurde, den Farbbeitrag nach Shading-Modellen ermitteln
        if (gewinner >=0){
            // Schnittinformationen speichern.
            s = s_treffer;
            // # Lambertian Shading: ....
            float beleuchtung = 0;
            for(int i=0; i<szene.anzObjekte; i++){
                if (szene.objekte[i]->material.emission > 0){
                    // Objekt hat emmisionsmaterial
                    // Vektor der den schnittpunkt mit der lichtquelle verbindet
                    TVektor richtung = szene.objekte[i]->position - s.schnittpunkt;
                    Strahl lichtstrahl(s.schnittpunkt, richtung);
                    lichtstrahl = szene.objekte[i]->schnitt(lichtstrahl);
                    if (lichtstrahl.entfernung < Norm(richtung)){
                        // wenn schnittpunkt n�her dran als die aktuelle emmisionsquelle
                        float parral;
                        parral = parralelitaetZweiVektoren(lichtstrahl.richtung, s.normale);
                        beleuchtung += (parral - 1) * -1;
                    }
                }
            }
            int r = int(GetRValue(szene.objekte[gewinner]->material.farbe));
            int g = int(GetGValue(szene.objekte[gewinner]->material.farbe));
            int b = int(GetBValue(szene.objekte[gewinner]->material.farbe));
            if (beleuchtung > 1){beleuchtung = 1;}
            lambertian = TVektor(r,g,b) * beleuchtung;


            // Reflection Shading (nur, wenn Material reflektierend):
            if (szene.objekte[gewinner]->material.reflekt > 0){
                // Strahl reflektieren (Einfallswinkel = Ausfallswinkel).
                Strahl reflektionsStrahl;        
                reflektionsStrahl.richtung = s.richtung - 2 * (s.richtung * s.normale) * s.normale;
                reflektionsStrahl.ursprung = s.schnittpunkt+0.01*reflektionsStrahl.richtung;

                // Farbe rekursiv mit reflektiertem Strahl berechnen:
                TVektor reflection;
                reflection = berechneFarbe(szene,reflektionsStrahl,iteration-1);
            }

            // Farbbeitr�ge mischen:
                // TColor farbe;
                // farbe = szene.objekte[gewinner]->material->reflekt * reflection + ... * lambertian
                // return farbe;
        }

        if (szene.objekte[gewinner]->material.reflekt > 0){
            return szene.objekte[gewinner]->material.reflekt * reflection + lambertian * (1-szene.objekte[gewinner]->material.reflekt);
        }
        else{
            return lambertian;
        }
    }

    TColor farbeMischen(TColor c1, TColor c2, float anteil){
        // mischt zwei Farben c1 und c2
        // float anteil gibt den Anteil von c1 an, zwischen 0 und 1
        int r = int((anteil*GetRValue(c1)+(1-anteil)*GetRValue(c2)));
        int g = int((anteil*GetGValue(c1)+(1-anteil)*GetGValue(c2)));
        int b = int((anteil*GetBValue(c1)+(1-anteil)*GetBValue(c2)));
    return RGB(r,g,b);
    }





    void Init(){
        // Kamera initialisieren.
        TVektor kam_pos(7,-7,7);
        TVektor blick(-7,7,-7);
        TVektor oben(-7,7,7);

        const int XAUFL = 720;
        const int YAUFL = 480;
        const float BRENN = 5;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Szene initialisieren.
        szene = new Szene();
        szene->kugelHinzufuegen(TVektor(0,0,0), Rot, 0.5);
    }

    void Run(){
        // Durch jeden Pixel iterieren.
        for (int x=0; x<kamera->aufloesungX; x++){
            for (int y=0; y<kamera->aufloesungY; y++){
                TVektor f = berechneFarbe(*szene, kamera->gibStrahl(x,y), 7);
                TColor farbe(RGB(f[0],f[1],f[2]));
                SetPixel(x,y,farbe);
            }
        }
    }

};


//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
