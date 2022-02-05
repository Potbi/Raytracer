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

// Raytracing-Funktionen einbinden
#include "raytracer.h"

#include <time.h>

clock_t start, finish;

Kamera* kamera;
Szene* szene;

int totalpx;
int tilesize;
int currenttile;
int rows, columns;

class TUser : public TPlan {

    void Init(){
        // Kamera initialisieren.
        TVektor kam_pos(3,0,2.5);
        TVektor blick(0.965926,0.000000,-0.258819);
        TVektor oben(-0.258819,0.000000,-0.965926);

        const int XAUFL = 720;
        const int YAUFL = 480;
        const float BRENN =1;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Szene initialisieren.
        szene = new Szene();
        TColor Rosa = RGB(240,128,128);
        TColor Orange = RGB(255,218,185);

        Material erde(Weiss, 0, 0);
        Material kugelA(Rosa, 0.2, 0);
        Material kugelB(Orange, 0, 0);
        Material metall(Weiss,0.9,0);
        Material licht(Weiss, 0, 1.0);

        szene->kugelHinzufuegen(TVektor(10,0,-1000), erde, 1000);
        szene->lichtHinzufuegen(TVektor(6,1.5,4), 1);
        //szene->kugelHinzufuegen(TVektor(6,-1.5,4), licht, 0.2);
        szene->kugelHinzufuegen(TVektor(10,-4,0.5), metall, 0.5);
        szene->kugelHinzufuegen(TVektor(10,-1,1), kugelA, 1);
        szene->kugelHinzufuegen(TVektor(10,2.5,1.5), kugelB, 1.5);


        // Einstellungen für Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);
    }

    void Run(){
        // Laufzeitmessung starten
        if (currenttile == 0) {
            start = clock();
        }

        // aktuelle Kachel rendern
        CallRun = renderTile(currenttile);

        // Laufzeitmessung beenden
        if (currenttile == (columns * rows)) {
            finish = clock();
            Busy = PlanString("Fertig nach ") + ((double)(finish - start))/CLOCKS_PER_SEC + PlanString(" s.");
        }
    }

    float min(float a, float b){
        return((a<b) ? a : b);
    }

    bool renderTile(int &currenttile){
        // Rendert die Pixel im Bereich der aktuellen Kachel
        int currentrow = floor((float)currenttile/columns) + 1;
        int currentcolumn = currenttile % columns +1;
        bool finish = (((currenttile+1) < (columns * rows)) ? true : false);
        for (int x=(currentcolumn-1)*tilesize; x<min(currentcolumn*tilesize,kamera->aufloesungX); x++){
            Busy = PlanString("Fortschritt: ") + 100*totalpx/(kamera->aufloesungX*kamera->aufloesungY) + PlanString(" %");
            for (int y=(currentrow-1)*tilesize; y<min(currentrow*tilesize,kamera->aufloesungY); y++){
                TVektor f = berechneFarbe(*szene, kamera->gibStrahl(x,y), 6);
                TColor farbe(RGB(f[0],f[1],f[2]));
                SetPixel(x,y,farbe);
                totalpx++;
                }
            }
        currenttile++;
        return finish;
    }

};


//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
