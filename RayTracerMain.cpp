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

    TColor berechneFarbe(Szene szene, Strahl s){
        float abstand;
        float abstandMin  = std::numeric_limits<float>::infinity();     //unendlich
        TColor farbe = szene.hintergrund;

        int gewinner=-1;
        Strahl s_treffer;

        for(int i=0; i<szene.anzObjekte; i++){
            s = szene.objekte[i]->schnitt(s);
            if ((s.entfernung > 0)&&(s.entfernung < abstandMin)){
                abstandMin=s.entfernung;
                s_treffer=s;
                gewinner = i;
                //farbe = szene.objekte[i]->farbe;
            }
        }

        TVektor lambertian = TVektor(0,0,0);
        TVektor reflection;

        if (gewinner > -1){
        // # Lambertian Shading: ....
            float beleuchtung = 0;
            for(int i=0; i<szene.anzObjekte; i++){
                if (szene.objekte[i]->material.emission > 0){
                    Strahl lichtstrahl(s_treffer.schnittpunkt, szene.objekte[i]->position - s.schnittpunkt);
                    lichtstrahl = szene.objekte[i]->schnitt(lichtstrahl);
                    if (lichtstrahl.entfernung > 0){
                        float parralelitaet;
                        parralelitaet = parralelitaetZweiVektoren(lichtstrahl.richtung, s_treffer.normale);
                        beleuchtung *= (parralelitaet - 1) * -1;
                    }
                }
            }
            int r = int(GetRValue(cszene.objekte[gewinner]->material.farbe));
            int g = int(GetGValue(cszene.objekte[gewinner]->material.farbe));
            int b = int(GetBValue(cszene.objekte[gewinner]->material.farbe));
            lambertian = TVektor(r,g,b) * beleuchtung;
        }


        // szene.objekte[gewinner]->material->reflekt * reflection


        return farbe;
    }

    TColor farbeMischen(TColor c1, TColor c2){
        int r = int((GetRValue(c1)+GetRValue(c2))/2);
        int g = int((GetGValue(c1)+GetGValue(c2))/2);
        int b = int((GetBValue(c1)+GetBValue(c2))/2);
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
        for (int x=0; x<XAUFL; x++){
            for (int y=0; y<YAUFL; y++){
                SetPixel(x,y,berechneFarbe(*szene, kamera->gibStrahl(x,y)));
            }
        }
    }

};


//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
