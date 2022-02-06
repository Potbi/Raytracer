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
        TVektor kam_pos(3,0,0.5);
        TVektor blick(0.996195,0.000000,-0.087156);
        TVektor oben(-0.087156,0.000000,-0.996195);

        const int XAUFL = 720;
        const int YAUFL = 480;
        const float BRENN =2;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Szene initialisieren.
        szene = new Szene();

        TColor unirot = RGB(213,17,48);
        Material mtl_weiss(Weiss, 0);
        Material mtl_schwarz(Schwarz,0);
        Material mtl_unirot(unirot,0);
        Material mtl_metall(Weiss,0.9);


        // Licht
        szene->lichtHinzufuegen(TVektor(5,0.5,1.2), 1, 0.3);
        //szene->kugelHinzufuegen(TVektor(5,0.5,1.5), mtl_unirot, 0.3);

        // Ebene mit Schachbrett
        szene->ebeneHinzufuegen(TVektor(5,2.5,0),TVektor(0,-1,0),TVektor(1,0,0),5,5,mtl_weiss,mtl_schwarz);
        //szene->ebeneHinzufuegen(TVektor(5,2.5,5),TVektor(0,0,-1),TVektor(1,0,0),5,5,mtl_weiss,mtl_schwarz);

        // Kugeln
        szene->kugelHinzufuegen(TVektor(7.5,-1,0.5), mtl_metall, 0.5);
        szene->kugelHinzufuegen(TVektor(7.5,0.8,0.5), mtl_unirot, 0.5);


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
