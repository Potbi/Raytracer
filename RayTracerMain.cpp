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


class TUser : public TPlan {
    TColor berechneFarbe(Szene szene, Strahl s){
        float abstand;
        //float abstandMin  = std::numeric_limits<float>::infinity();//unendlich
        float abstandMin  = 100000;
        TColor farbe = szene.hintergrund;

        for(int i=0; i<szene.anzObjekte; i++){
                abstand = szene.objekte[i]->schnitt(s);
                if (abstand > 0){
                        if (abstand < abstandMin) {
                                abstandMin=abstand;
                                farbe = szene.objekte[i]->farbe;
                        }
                }
        }
        return farbe;
    }

    void Init(){



    }
    void Run(){
        //TVektor cam_pos(7.3589,-6.9258,4.9583);
        //TVektor blick(-7.3589,6.9258,-4.9583);
        //TVektor oben(-2.0,2.0,5.7619);
        TVektor cam_pos(7,-7,7);
        TVektor blick(-7,7,-7);
        TVektor oben(-7,7,7);
        //TVektor urspr(0,0,0);
        //TVektor blick(1,1,0);
        //TVektor oben(0,0,1);

        Kamera cam(cam_pos, blick, oben,720,480, 1);
        Szene szene1;
        szene1.kugelHinzufuegen(TVektor(0,0,0), Rot, 0.5);
        //szene1.kugelHinzufuegen(TVektor(2,0,0), Blau, 0.2);
        //szene1.kugelHinzufuegen(TVektor(1,0,0), Gelb, 0.05);

        Strahl s(urspr, blick);
        szene1.objekte[0]->schnitt(s);
        //Strahl* strahl;
        //strahl = cam.gibStrahl(1,1);
        //std::cout<<strahl->richtung[0]<<strahl->richtung[1]<<strahl->richtung[2];
        //std::cout<<cam.oben[0]<<cam.oben[1]<<cam.oben[2];
        TColor farbe;
        for (int x=0; x<720; x++){
                for (int y=0; y<480; y++){

                //strahl = cam.gibStrahl(x,y);
                farbe = berechneFarbe(szene1, cam.gibStrahl(x,y));
                SetPixel(x,y,farbe);

                }
        }


    }

};


//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
