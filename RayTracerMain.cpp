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

class TUser : public TPlan {

    void Diamant(){
        Material mtl_dia(Weiss,0.9);
        szene->dreieckHinzufuegen(TVektor(0.088642,-0.079207,0.469923),TVektor(-0.106926,0.120328,0.457217),TVektor(-0.295841,-0.069904,0.377559),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.220308,0.053448,0.123503),TVektor(-0.115909,0.158576,0.167524),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.336217,0.212024,0.291028),TVektor(-0.219903,0.288885,0.332988),TVektor(-0.115909,0.158576,0.167524),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.412808,0.094635,0.251648),TVektor(-0.336217,0.212024,0.291028),TVektor(-0.220308,0.053448,0.123503),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.142411,0.044672,0.210639),TVektor(0.145011,-0.107636,0.184477),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.287423,-0.062964,0.395116),TVektor(0.262214,-0.203010,0.364313),TVektor(0.145011,-0.107636,0.184477),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.257410,0.078418,0.412654),TVektor(0.287423,-0.062964,0.395116),TVektor(0.142411,0.044672,0.210639),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.145011,-0.107636,0.184477),TVektor(0.040611,-0.212764,0.140456),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.185622,-0.320400,0.324933),TVektor(0.069308,-0.397261,0.282972),TVektor(0.040611,-0.212764,0.140456),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.262214,-0.203010,0.364313),TVektor(0.185622,-0.320400,0.324933),TVektor(0.145011,-0.107636,0.184477),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.040611,-0.212764,0.140456),TVektor(-0.109632,-0.209128,0.104363),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.069021,-0.421892,0.244819),TVektor(-0.208305,-0.390544,0.216281),TVektor(-0.109632,-0.209128,0.104363),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.069308,-0.397261,0.282972),TVektor(-0.069021,-0.421892,0.244819),TVektor(0.040611,-0.212764,0.140456),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.034335,0.154941,0.203617),TVektor(0.142411,0.044672,0.210639),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.176746,0.199613,0.414257),TVektor(0.257410,0.078418,0.412654),TVektor(0.142411,0.044672,0.210639),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.057711,0.282168,0.399679),TVektor(0.176746,0.199613,0.414257),TVektor(0.034335,0.154941,0.203617),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.153733,0.031066,0.462758),TVektor(0.004991,0.182825,0.453093),TVektor(0.029984,0.059959,0.480067),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.004991,0.182825,0.453093),TVektor(0.176746,0.199613,0.414257),TVektor(0.057711,0.282168,0.399679),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.057711,0.282168,0.399679),TVektor(-0.081574,0.313517,0.371142),TVektor(0.004991,0.182825,0.453093),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.004991,0.182825,0.453093),TVektor(-0.106926,0.120328,0.457217),TVektor(0.029984,0.059959,0.480067),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.157311,-0.178550,0.426751),TVektor(0.153733,0.031066,0.462758),TVektor(0.088642,-0.079207,0.469923),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.153733,0.031066,0.462758),TVektor(0.287423,-0.062964,0.395116),TVektor(0.257410,0.078418,0.412654),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.257410,0.078418,0.412654),TVektor(0.176746,0.199613,0.414257),TVektor(0.153733,0.031066,0.462758),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.153733,0.031066,0.462758),TVektor(0.029984,0.059959,0.480067),TVektor(0.088642,-0.079207,0.469923),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.013629,-0.323233,0.366167),TVektor(0.157311,-0.178550,0.426751),TVektor(0.034688,-0.215648,0.432726),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.157311,-0.178550,0.426751),TVektor(0.185622,-0.320400,0.324933),TVektor(0.262214,-0.203010,0.364313),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.262214,-0.203010,0.364313),TVektor(0.287423,-0.062964,0.395116),TVektor(0.157311,-0.178550,0.426751),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.157311,-0.178550,0.426751),TVektor(0.088642,-0.079207,0.469923),TVektor(0.034688,-0.215648,0.432726),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.193145,-0.318230,0.316493),TVektor(0.013629,-0.323233,0.366167),TVektor(-0.100273,-0.269439,0.390266),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.013629,-0.323233,0.366167),TVektor(-0.069021,-0.421892,0.244819),TVektor(0.069308,-0.397261,0.282972),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.069308,-0.397261,0.282972),TVektor(0.185622,-0.320400,0.324933),TVektor(0.013629,-0.323233,0.366167),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.013629,-0.323233,0.366167),TVektor(0.034688,-0.215648,0.432726),TVektor(-0.100273,-0.269439,0.390266),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.341887,-0.166471,0.306829),TVektor(-0.193145,-0.318230,0.316493),TVektor(-0.237182,-0.209070,0.367415),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.193145,-0.318230,0.316493),TVektor(-0.327341,-0.307988,0.201704),TVektor(-0.208305,-0.390544,0.216281),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.208305,-0.390544,0.216281),TVektor(-0.069021,-0.421892,0.244819),TVektor(-0.193145,-0.318230,0.316493),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.193145,-0.318230,0.316493),TVektor(-0.100273,-0.269439,0.390266),TVektor(-0.237182,-0.209070,0.367415),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.345465,0.043145,0.342835),TVektor(-0.341887,-0.166471,0.306829),TVektor(-0.295841,-0.069904,0.377559),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.341887,-0.166471,0.306829),TVektor(-0.438017,-0.045412,0.220844),TVektor(-0.408005,-0.186794,0.203306),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.408005,-0.186794,0.203306),TVektor(-0.327341,-0.307988,0.201704),TVektor(-0.341887,-0.166471,0.306829),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.341887,-0.166471,0.306829),TVektor(-0.237182,-0.209070,0.367415),TVektor(-0.295841,-0.069904,0.377559),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.201783,0.187828,0.403420),TVektor(-0.345465,0.043145,0.342835),TVektor(-0.241886,0.066537,0.414756),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.345465,0.043145,0.342835),TVektor(-0.336217,0.212024,0.291028),TVektor(-0.412808,0.094635,0.251648),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.412808,0.094635,0.251648),TVektor(-0.438017,-0.045412,0.220844),TVektor(-0.345465,0.043145,0.342835),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.345465,0.043145,0.342835),TVektor(-0.295841,-0.069904,0.377559),TVektor(-0.241886,0.066537,0.414756),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.004991,0.182825,0.453093),TVektor(-0.201783,0.187828,0.403420),TVektor(-0.106926,0.120328,0.457217),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.201783,0.187828,0.403420),TVektor(-0.081574,0.313517,0.371142),TVektor(-0.219903,0.288885,0.332988),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.219903,0.288885,0.332988),TVektor(-0.336217,0.212024,0.291028),TVektor(-0.201783,0.187828,0.403420),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.201783,0.187828,0.403420),TVektor(-0.241886,0.066537,0.414756),TVektor(-0.106926,0.120328,0.457217),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.217709,-0.098860,0.097341),TVektor(-0.220308,0.053448,0.123503),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.438017,-0.045412,0.220844),TVektor(-0.412808,0.094635,0.251648),TVektor(-0.220308,0.053448,0.123503),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.408005,-0.186794,0.203306),TVektor(-0.438017,-0.045412,0.220844),TVektor(-0.217709,-0.098860,0.097341),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.109632,-0.209128,0.104363),TVektor(-0.217709,-0.098860,0.097341),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.327341,-0.307988,0.201704),TVektor(-0.408005,-0.186794,0.203306),TVektor(-0.217709,-0.098860,0.097341),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.208305,-0.390544,0.216281),TVektor(-0.327341,-0.307988,0.201704),TVektor(-0.109632,-0.209128,0.104363),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.115909,0.158576,0.167524),TVektor(0.034335,0.154941,0.203617),TVektor(0.000000,0.000000,-0.000000),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.081574,0.313517,0.371142),TVektor(0.057711,0.282168,0.399679),TVektor(0.034335,0.154941,0.203617),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.219903,0.288885,0.332988),TVektor(-0.081574,0.313517,0.371142),TVektor(-0.115909,0.158576,0.167524),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.295841,-0.069904,0.377559),TVektor(-0.237182,-0.209070,0.367415),TVektor(-0.100273,-0.269439,0.390266),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.100273,-0.269439,0.390266),TVektor(0.034688,-0.215648,0.432726),TVektor(0.088642,-0.079207,0.469923),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.088642,-0.079207,0.469923),TVektor(0.029984,0.059959,0.480067),TVektor(-0.106926,0.120328,0.457217),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.106926,0.120328,0.457217),TVektor(-0.241886,0.066537,0.414756),TVektor(-0.295841,-0.069904,0.377559),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.295841,-0.069904,0.377559),TVektor(-0.100273,-0.269439,0.390266),TVektor(0.088642,-0.079207,0.469923),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.220308,0.053448,0.123503),TVektor(-0.336217,0.212024,0.291028),TVektor(-0.115909,0.158576,0.167524),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.142411,0.044672,0.210639),TVektor(0.287423,-0.062964,0.395116),TVektor(0.145011,-0.107636,0.184477),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.145011,-0.107636,0.184477),TVektor(0.185622,-0.320400,0.324933),TVektor(0.040611,-0.212764,0.140456),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.040611,-0.212764,0.140456),TVektor(-0.069021,-0.421892,0.244819),TVektor(-0.109632,-0.209128,0.104363),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.034335,0.154941,0.203617),TVektor(0.176746,0.199613,0.414257),TVektor(0.142411,0.044672,0.210639),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.153733,0.031066,0.462758),TVektor(0.176746,0.199613,0.414257),TVektor(0.004991,0.182825,0.453093),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.157311,-0.178550,0.426751),TVektor(0.287423,-0.062964,0.395116),TVektor(0.153733,0.031066,0.462758),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.013629,-0.323233,0.366167),TVektor(0.185622,-0.320400,0.324933),TVektor(0.157311,-0.178550,0.426751),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.193145,-0.318230,0.316493),TVektor(-0.069021,-0.421892,0.244819),TVektor(0.013629,-0.323233,0.366167),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.341887,-0.166471,0.306829),TVektor(-0.327341,-0.307988,0.201704),TVektor(-0.193145,-0.318230,0.316493),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.345465,0.043145,0.342835),TVektor(-0.438017,-0.045412,0.220844),TVektor(-0.341887,-0.166471,0.306829),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.201783,0.187828,0.403420),TVektor(-0.336217,0.212024,0.291028),TVektor(-0.345465,0.043145,0.342835),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(0.004991,0.182825,0.453093),TVektor(-0.081574,0.313517,0.371142),TVektor(-0.201783,0.187828,0.403420),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.217709,-0.098860,0.097341),TVektor(-0.438017,-0.045412,0.220844),TVektor(-0.220308,0.053448,0.123503),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.109632,-0.209128,0.104363),TVektor(-0.327341,-0.307988,0.201704),TVektor(-0.217709,-0.098860,0.097341),mtl_dia);
        szene->dreieckHinzufuegen(TVektor(-0.115909,0.158576,0.167524),TVektor(-0.081574,0.313517,0.371142),TVektor(0.034335,0.154941,0.203617),mtl_dia);

    }

    void Init(){
        // Kamera initialisieren.
        TVektor kam_pos(-3,0,0.7);
        TVektor blick(0.996195,0.000000,-0.087156);
        TVektor oben(-0.087156,0.000000,-0.996195);

        const int XAUFL = 720;
        const int YAUFL = 480;
        const float BRENN =2.2;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Szene initialisieren.
        szene = new Szene();

        TColor unirot = RGB(213,17,48);
        TColor grau = RGB(70,70,70);

        Material mtl_weiss(Weiss, 0);
        Material mtl_schwarz(grau,0);
        Material mtl_unirot(unirot,0);
        Material mtl_metall(Weiss,0.9);
        Material mtl_gelb(Gelb,0);


        // Licht
        szene->lichtHinzufuegen(TVektor(-30,10,30), 1, 0.3);

        // Ebene mit Schachbrettmuster
        szene->ebeneHinzufuegen(TVektor(-2,2,0),TVektor(0,-1,0),TVektor(1,0,0),4,4,mtl_weiss,mtl_schwarz);

        // Kugeln zufaellig hinzufuegen
        const int N = 50;
        int i=0;
        while (i<N){
            float x = static_cast< float >(rand() % 400 - 199)/100.0;
            float y = static_cast< float >(rand() % 400 - 199)/100.0;
            if ( ((x<-0.5)||(x>0.5)) && ((y<-0.5)||(y>0.5)) ) {
                i++;
                float r = static_cast< float >(rand() % 25 +1)/100.0;
                float z = static_cast< float >(rand() % 200 +1)/100.0;
                int level = (rand() % 10);
                int farbe = (rand() % 10);
                z = ((level>5) ? r : z);
                if (farbe == 3) {
                    szene->kugelHinzufuegen(TVektor(x,y,z), mtl_metall, r);
                }
                if ((farbe>4)&&(farbe!=3)) {
                    szene->kugelHinzufuegen(TVektor(x,y,z), mtl_gelb, r);
                } else {
                    szene->kugelHinzufuegen(TVektor(x,y,z), mtl_unirot, r);
                }
            }
        }

        // Diamant hinzufuegen
        Diamant();


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
