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
#include <time.h> 

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

            // ### LAMBERTIAN SHADING ###
            TVektor lambertian;
            float beleuchtung = 0;
            for(int i=0; i<szene.anzObjekte; i++){
                if (szene.objekte[i]->material.emission > 0){
                    // Objekt hat emmisionsmaterial
                    // Vektor der den schnittpunkt mit der lichtquelle verbindet

                    TVektor richtung = szene.objekte[i]->position - s_treffer.schnittpunkt;
                    Strahl lichtstrahl(s_treffer.schnittpunkt+richtung*(-0.01), richtung);

                    abstandMin  = std::numeric_limits<float>::infinity();
                    int gewinner_licht = -1;
                    for(int j=0; j<szene.anzObjekte; j++){
                        lichtstrahl = szene.objekte[j]->schnitt(lichtstrahl);
                        if ((lichtstrahl.entfernung > 0)&&(lichtstrahl.entfernung < abstandMin)){
                            abstandMin=lichtstrahl.entfernung;
                            gewinner_licht = j;
                        }
                    }

                    if (gewinner_licht >= 0){
                        //lichtstrahl = szene.objekte[gewinner_licht]->schnitt(lichtstrahl);
                        if (szene.objekte[gewinner_licht]==szene.objekte[i]){
                            // wenn schnittpunkt n�her dran als die aktuelle emmisionsquelle
                            float parral;
                            parral = parallelitaetZweiVektoren(lichtstrahl.richtung, s_treffer.normale);
                            beleuchtung += parral;
                        }
                    }
                    
                }
            }
            int r = int(GetRValue(szene.objekte[gewinner]->material.farbe));
            int g = int(GetGValue(szene.objekte[gewinner]->material.farbe));
            int b = int(GetBValue(szene.objekte[gewinner]->material.farbe));
            if (beleuchtung > 1){beleuchtung = 1;}
            lambertian = TVektor(r,g,b) * beleuchtung;


            // ### REFLECTION SHADING ### (nur, wenn Material reflektierend)
            TVektor reflection;
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
            return reflection*ref_anteil+lambertian*(1-ref_anteil);
            //return lambertian;
        }
        // Wenn kein Objekt geschnitten wurde, Hintergrundfarbe zurueckgeben.
        TColor hintergrund = hintergrundFarbe(s.richtung[2],-1,1);
        return TVektor(GetRValue(hintergrund),GetGValue(hintergrund),GetBValue(hintergrund));
    }

    float map(float x, float start1, float stop1, float start2, float stop2){
        return(start2+((x-start1)/(stop1-start1))*(stop2-start2));
    }

    TColor hintergrundFarbe(float x, float start, float stop){
        int r = (int)(map(x,start,stop,255,20)*100.0/255);
        int g = (int)(map(x,start,stop,255,100)*100.0/255);
        int b = (int)(map(x,start,stop,255,200)*100.0/255);
        return RGBSkala(r,g,b);
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
        TVektor kam_pos(7,0,7);
        TVektor blick(-7,0,-7);
        TVektor oben(7,0,-7);

        const int XAUFL = 480;
        const int YAUFL = 360;
        const float BRENN = 1.5;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Szene initialisieren.
        szene = new Szene();
        Material mtl_rot(Rot, 0.05, 0);
        Material mtl_s(Rot, 1, 0);
        Material mtl_leuchte(Weiss, 0, 1);
        szene->kugelHinzufuegen(TVektor(0,-3,0), mtl_s, 1);
        szene->kugelHinzufuegen(TVektor(0,3,0), mtl_s, 1);
        szene->kugelHinzufuegen(TVektor(0,0,5), mtl_leuchte, 0.1);
        szene->kugelHinzufuegen(TVektor(0,0,0), mtl_rot, 1);
        szene->kugelHinzufuegen(TVektor(0,0,2), mtl_rot, 0.4);
    }

    void Run(){
        // Durch jeden Pixel iterieren.
        double time1=0.0, tstart;       // time measurment variables
        tstart = clock();               // start
        for (int x=0; x<kamera->aufloesungX; x++){
            for (int y=0; y<kamera->aufloesungY; y++){
                TVektor f = berechneFarbe(*szene, kamera->gibStrahl(x,y), 3);
                TColor farbe(RGB(f[0],f[1],f[2]));
                SetPixel(x,y,farbe);
                totalpx++;
                Busy = PlanString("Fortschritt: ") + 100*totalpx/(kamera->aufloesungX*kamera->aufloesungY) + PlanString(" %");
            }
        }
        time1 += clock() - tstart;     // end
        time1 = time1/CLOCKS_PER_SEC;  // rescale to seconds
        std::cout << "  time = " << time1 << " sec. \n";
    }

};


//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
