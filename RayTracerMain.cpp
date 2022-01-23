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

    TColor berechneFarbe(Szene szene, Strahl s){
        float abstand;
        float abstandMin  = std::numeric_limits<float>::infinity();//unendlich
        TColor farbe = szene.hintergrund;

        for(int i=0; i<szene.anzObjekte; i++){
            abstand = szene.objekte[i]->schnitt(s);
            if ((abstand > 0)&&(abstand < abstandMin)){
                abstandMin=abstand;
                farbe = szene.objekte[i]->farbe;
            }
        }
        return farbe;
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
