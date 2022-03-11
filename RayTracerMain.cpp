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
#include <stdlib.h>     /* srand, rand */

clock_t start, finish;

Kamera* kamera;
Szene* szene;

int totalpx;
int tilesize;
int currenttile;
int rows, columns;
bool rendern = false;

class TUser : public TPlan {

    void Leer(){
        Clear();
        kamera = new Kamera();
        szene = new Szene();
        // Einstellungen für Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);
    }

    void NKugeln(int n){
        // Szenen-Einstellungen.
        TVektor kam_pos(0,0,0);
        TVektor blick(1,0,0);
        TVektor oben(0,0,-1);

        const int XAUFL = GetMaxW()/4;
        const int YAUFL = GetMaxH()/4;
        const float BRENN = 2;

        // Alte Szene loeschen, neue Szene aufbauen.
        Clear();
        delete szene;
        delete kamera;
        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);
        szene = new Szene();

        // Kugeln.
        Material mtl_weiss(Weiss, 0);
        szene->lichtHinzufuegen(TVektor(-100,-100,100),1);

        float x,y;
        for (int i=0; i<n; i++){
            //x = 0 + 1*(float(i)/10)*cos(i*3.141592654/5);
            //y = 0 + 1*(float(i)/10)*sin(i*3.141592654/5);
            szene->kugelHinzufuegen(TVektor(5+0.02*i,0,0),mtl_weiss,2);
        }

        // Einstellungen für Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);
    }


    void Init(){
        ProgrammName = "Einfacher Ray-Tracing Renderer";
        ProgrammInfo = "Simulation komplexer System WS21/22\nJoern Froboese\nKatja Ruge\nMaximilian Kens";

        InsertTaste(0, "Leer", "lädt Leere Szene");
        InsertTaste(1, "Laufzeit1", "Kugeln");
        InsertTaste(2, "Laufzeit1", "Kugeln");

        Leer();
    }

    void Run(){
        /*
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
        */
        rendern = renderTile(currenttile);
    }

    void RunTaste0(){
        Leer();
    }

    void RunTaste1(){
        std::cout <<  "[";
        for (int i = 0; i<40; i++){
            totalpx = 0;
            NKugeln(i);
            start = clock();

            rendern = true;
            while(rendern){
                // aktuelle Kachel rendern
                Run();
            }

            finish = clock();
            std::cout << i << "," <<  ((double)(finish - start))/CLOCKS_PER_SEC << ";";
        }
        std::cout <<  "]";
    }

    void RunTaste2(){

    }

    void Finish(){
        delete szene;
        delete kamera;
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
                TVektor f = berechneFarbe(szene, kamera->gibStrahl(x,y), 6);
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
