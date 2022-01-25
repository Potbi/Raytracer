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

    TColor berechneFarbe(Szene szene, Strahl s, int iteration){

        // Abbruchbedingung Rekursion: wenn maximale Anzahl Strahlen erreicht -> keinen Farbbeitrag mehr ermitteln.
        if (iteration == 0) return Schwarz;

        // Strahl mit der Szene schneiden und vorderstes Schnittobjekt mit Index i ermitteln.
        float abstand;
        float abstandMin  = std::numeric_limits<float>::infinity();
        int gewinner = -1;
        for(int i=0; i<szene.anzObjekte; i++){
            abstand = szene.objekte[i]->schnitt(s).entfernung;
            if ((abstand > 0)&&(abstand < abstandMin)){
                abstandMin = abstand;
                gewinner = i;
            }
        }

        // Wenn ein Objekt geschnitten wurde, den Farbbeitrag nach Shading-Modellen ermitteln
        if (gewinner >=0){
            // Schnittinformationen speichern.
            s = szene.objekte[gewinner]->schnitt(s);

            // Lambertian Shading:
            TVektor lambertian;

            // Reflection Shading (nur, wenn Material reflektierend):
            if (szene.objekte[gewinner]->material->reflekt > 0){
                // Strahl reflektieren (Einfallswinkel = Ausfallswinkel).
                Strahl reflektionsStrahl;
                reflektionsStrahl.ursprung = s.schnittpunkt+0.01*s.normale;
                reflektionsStrahl.richtung = s.richtung - 2 * (s.richtung * s.normal) * s.normal;

                // Farbe rekursiv mit reflektiertem Strahl berechnen:
                TColor reflection;
                reflection = berechneFarbe(szene,reflektionsStrahl,iteration-1);
            }

            // Farbbeiträge mischen:
                // TColor farbe;
                // farbe = szene.objekte[gewinner]->material->reflekt * reflection + ... * lambertian
                // return farbe;
        }

        // Wenn kein Objekt getroffen wurde, Hintergrundfarbe der Szene zurückgeben.
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
                SetPixel(x,y,berechneFarbe(*szene, kamera->gibStrahl(x,y)));
            }
        }
    }

};


//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
