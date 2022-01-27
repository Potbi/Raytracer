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
#include "material.h"

Kamera* kamera;
Szene* szene;

int totalpx;

class TUser : public TPlan {
    float abs(float zahl){
        return((zahl > 0) ? zahl : -zahl);
    }
    float parallelitaetZweiVektoren(TVektor a, TVektor b){
                // winkel zwischen Vektoren von 0-1
                // 1 = Parallel, 0 = Orthogonal
                float top;
                float bottom;
                top = a*b;
                bottom = Norm(a)*Norm(b);
                float temp = top/bottom;
                return abs(temp);
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
            Strahl s2 = szene.objekte[i]->schnitt(s);
            //std::cout<<s2.entfernung<<"\n";
            //szene.objekte[i]->schnitt(s);
            if ((s2.entfernung > 0)&&(s2.entfernung < abstandMin)){
                abstandMin=s2.entfernung;
                //std::cout<<"("<<s2.richtung[0]<<","<<s2.richtung[1]<<","<<s2.richtung[2]<<")\n";
                s_treffer = Strahl(s2); // ACHTUNG
                //std::cout<<"("<<s_treffer.richtung[0]<<","<<s_treffer.richtung[1]<<","<<s_treffer.richtung[2]<<")\n";
                gewinner = i;

            }

        }
        // Wenn kein Objekt getroffen wurde, Hintergrundfarbe der Szene zurueckgeben.
        TVektor lambertian = szene.hintergrund;
        TVektor reflection = NULL;

        // Wenn ein Objekt geschnitten wurde, den Farbbeitrag nach Shading-Modellen ermitteln
        if (gewinner >=0){
            // Schnittinformationen speichern.
            Strahl s(s_treffer);
            // # Lambertian Shading: ....
            std::cout<<"("<<s_treffer.richtung[0]<<","<<s_treffer.richtung[1]<<","<<s_treffer.richtung[2]<<")\n";
            float beleuchtung = 0;
            for(int i=0; i<szene.anzObjekte; i++){
                if (szene.objekte[i]->material.emission > 0){
                    // Objekt hat emmisionsmaterial
                    // Vektor der den schnittpunkt mit der lichtquelle verbindet
                    TVektor richtung = szene.objekte[i]->position - s.schnittpunkt;
                    Strahl lichtstrahl(s.schnittpunkt, richtung);
                    Strahl lichtstrahl2(szene.objekte[i]->schnitt(lichtstrahl));
                    if (lichtstrahl2.entfernung < Norm(richtung)){
                        // wenn schnittpunkt n�her dran als die aktuelle emmisionsquelle
                        float parral;
                        std::cout<<"("<<lichtstrahl2.richtung[0]<<","<<lichtstrahl2.richtung[1]<<","<<lichtstrahl2.richtung[2]<<")\n";
                        std::cout<<"("<<s.normale[0]<<","<<s.normale[1]<<","<<s.normale[2]<<")\n";
                        parral = parallelitaetZweiVektoren(lichtstrahl2.richtung, s.normale);
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

            if (szene.objekte[gewinner]->material.reflekt > 0){
                return szene.objekte[gewinner]->material.reflekt * reflection + lambertian * (1-szene.objekte[gewinner]->material.reflekt);
            }
            else{
                return lambertian;
            }
        }

        return szene.hintergrund;
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

        const int XAUFL = 20;
        const int YAUFL = 20;
        const float BRENN = 5;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Szene initialisieren.
        szene = new Szene();
        Material mtl_rot(Rot, 0, 0);
        Material mtl_leuchte(Weiss, 0, 1);
        szene->kugelHinzufuegen(TVektor(0,0,0), mtl_rot, 3.5);
        szene->kugelHinzufuegen(TVektor(10,-10,10), mtl_leuchte, 0.5);
    }

    void Run(){
        // Durch jeden Pixel iterieren.
        for (int x=0; x<kamera->aufloesungX; x++){
            for (int y=0; y<kamera->aufloesungY; y++){
                TVektor f = berechneFarbe(*szene, kamera->gibStrahl(x,y), 7);
                TColor farbe(RGB(f[0],f[1],f[2]));
                SetPixel(x,y,farbe);
                totalpx++;
                Busy = PlanString("Fortschritt: ") + 100*totalpx/(kamera->aufloesungX*kamera->aufloesungY) + PlanString(" %");
            }
        }
    }

};


//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
