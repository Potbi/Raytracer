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
                //std::cout<<"("<<a[0]<<","<<a[1]<<","<<a[2]<<")\n";
                //std::cout<<"("<<b[0]<<","<<b[1]<<","<<b[2]<<")\n";
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
                s_treffer = s2; // ACHTUNG
                gewinner = i;

            }

        }
        // Wenn kein Objekt getroffen wurde, Hintergrundfarbe der Szene zurueckgeben.
        TVektor lambertian = szene.hintergrund;
        TVektor reflection = NULL;

        // Wenn ein Objekt geschnitten wurde, den Farbbeitrag nach Shading-Modellen ermitteln
        if (gewinner >=0){
            // Schnittinformationen speichern.;
            // # Lambertian Shading: ....
            float beleuchtung = 0;
            for(int i=0; i<szene.anzObjekte; i++){
                if (szene.objekte[i]->material.emission > 0){
                    // Objekt hat emmisionsmaterial
                    // Vektor der den schnittpunkt mit der lichtquelle verbindet

                    TVektor richtung = szene.objekte[i]->position - s_treffer.schnittpunkt;
                    Strahl lichtstrahl(s_treffer.schnittpunkt, richtung);
                    Strahl lichtstrahl2 = szene.objekte[i]->schnitt(lichtstrahl);

                    if (lichtstrahl2.entfernung < Norm(richtung)){
                        // wenn schnittpunkt n�her dran als die aktuelle emmisionsquelle
                        float parral;
                        parral = parallelitaetZweiVektoren(lichtstrahl2.richtung, s_treffer.normale);
                        beleuchtung += parral;
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
                reflektionsStrahl.richtung = s_treffer.richtung - 2 * (s_treffer.richtung * s_treffer.normale) * s_treffer.normale;
                reflektionsStrahl.ursprung = s_treffer.schnittpunkt+0.01*reflektionsStrahl.richtung;

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
        TVektor kam_pos(7,0,0);
        TVektor blick(-7,0,0);
        TVektor oben(0,7,0);

        const int XAUFL = 300;
        const int YAUFL = 300;
        const float BRENN = 1;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Szene initialisieren.
        szene = new Szene();
        szene->hintergrund = Rot;
        Material mtl_rot(Rot, 0, 0);
        Material mtl_spiegel(Rot, 1, 0);
        Material mtl_leuchte(Weiss, 0, 1);
        szene->kugelHinzufuegen(TVektor(0,0,2), mtl_rot, 2);
        szene->kugelHinzufuegen(TVektor(0,0,-2), mtl_spiegel, 2);
        szene->kugelHinzufuegen(oben, mtl_leuchte, 0.5);
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
