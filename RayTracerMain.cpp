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

int bildschirmbruchteil = 14;

int totalpx;
int tilesize;
int currenttile;
int rows, columns;

class TUser : public TPlan {

    void Leer(){
        kamera = new Kamera();
        szene = new Szene();
        // Einstellungen f�r Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);
    }

    void DreiKugeln (){

            // Kamera initialisieren.
        TVektor kam_pos(-3,0,0.7);
        TVektor blick(0.996195,0.000000,-0.087156);
        TVektor oben(-0.087156,0.000000,-0.996195);

        const int XAUFL = GetMaxW()/bildschirmbruchteil;
        const int YAUFL = GetMaxH()/bildschirmbruchteil;
        const float BRENN =2.2;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Einstellungen f�r Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);

        // Szene initialisieren.
        szene = new Szene();

        Material mtl_weiss(Weiss, 0);
        Material mtl_schwarz(Schwarz,0);
        Material mtl_matt(Gruen,0);
        Material mtl_spiegel(Gruen,1);
        Material mtl_halbspiegel(Gruen,0.5);

        // Licht
        szene->lichtHinzufuegen(TVektor(-30,10,30), 0.3);

        // Ebene mit Schachbrettmuster
        szene->ebeneHinzufuegen(TVektor(-2,2,0),TVektor(0,-1,0),TVektor(1,0,0),4,4,mtl_weiss,mtl_schwarz,0.5);

        //Kugeln
        szene->kugelHinzufuegen(TVektor(0,-1,0.3), mtl_matt, 0.3);
        szene->kugelHinzufuegen(TVektor(0,0,0.3), mtl_halbspiegel, 0.3);
        szene->kugelHinzufuegen(TVektor(0,1,0.3), mtl_spiegel, 0.3);


    }

    void Diamant(){

        // Kamera initialisieren.
        TVektor kam_pos(-3,0,0.7);
        TVektor blick(0.996195,0.000000,-0.087156);
        TVektor oben(-0.087156,0.000000,-0.996195);

        const int XAUFL = GetMaxW()/bildschirmbruchteil;
        const int YAUFL = GetMaxH()/bildschirmbruchteil;
        const float BRENN =2.2;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Einstellungen f�r Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);

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
        szene->lichtHinzufuegen(TVektor(-30,10,30), 0.3);

        // Ebene mit Schachbrettmuster
        szene->ebeneHinzufuegen(TVektor(-2,2,0),TVektor(0,-1,0),TVektor(1,0,0),4,4,mtl_weiss,mtl_schwarz,0.5);

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

    void Tunnel(){

        // Kamera initialisieren.
        TVektor kam_pos(-3,0.8,0.2);
        TVektor blick(1,0,0);
        TVektor oben(0,0,1);

        const int XAUFL = GetMaxW()/bildschirmbruchteil;
        const int YAUFL = GetMaxH()/bildschirmbruchteil;
        const float BRENN =1;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Einstellungen f�r Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);

        // Szene initialisieren.
        szene = new Szene();

        TColor unirot = RGB(213,17,48);
        TColor grau = RGB(70,70,70);

        Material mtl_weiss(Weiss, 0);
        Material mtl_schwarz(grau,0);
        Material mtl_unirot(unirot,0);
        Material mtl_metall(Weiss,0.9);
        Material mtl_spiegel(Weiss,1);
        Material mtl_gelb(Gelb,0);


        // Licht
        szene->lichtHinzufuegen(TVektor(-6,0,0), 0.3);

        // Tunnel aus Ebenen
        szene->ebeneHinzufuegen(TVektor(-2,2,-1),TVektor(0,-1,0),TVektor(1,0,0),4,12,mtl_metall,mtl_metall,0.5);
        szene->ebeneHinzufuegen(TVektor(-2,2,1),TVektor(0,-1,0),TVektor(1,0,0),4,12,mtl_metall,mtl_metall,0.5);
        szene->ebeneHinzufuegen(TVektor(-2,2,-1),TVektor(0,0,1),TVektor(1,0,0),2,12,mtl_metall,mtl_metall,0.5);
        szene->ebeneHinzufuegen(TVektor(-2,-2,-1),TVektor(0,0,1),TVektor(1,0,0),2,12,mtl_metall,mtl_metall,0.5);

        // Kugeln zufaellig hinzufuegen
        const int N = 10;
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
    }

    void Face(){

            // Kamera initialisieren.
        TVektor kam_pos(2.7,0,-2);
        TVektor blick(-1,0,1);
        TVektor oben(0,-1,0);


        const int XAUFL = GetMaxH()/(bildschirmbruchteil);
        const int YAUFL = GetMaxH()/(bildschirmbruchteil);
        const float BRENN =2.6;

        kamera = new Kamera(kam_pos, blick, oben, XAUFL, YAUFL, BRENN);

        // Einstellungen f�r Kachel-Rendern.
        tilesize = 40;
        currenttile = 0;
        columns = ceil((float)kamera->aufloesungX/tilesize);
        rows = ceil((float)kamera->aufloesungY/tilesize);

        // Szene initialisieren.
        szene = new Szene();

        Material mtl_weiss(Weiss, 0);
        Material mtl_schwarz(Schwarz,0);
        Material mtl_Rot(Rot,0.3);
        Material mtl_spiegel(Weiss,0.9);
        Material mtl_dunkelrot(RGBSkala(33,0,0),0);
        Material mtl_haut(RGBSkala(100,59,33),0);

        // Licht
        szene->lichtHinzufuegen(TVektor(3,0,-3), 0.3);

        //Dreiecke
        szene->dreieckHinzufuegen(TVektor(0.252478,0.250623,0.050021),TVektor(0.272111,0.424200,0.131681),TVektor(0.152994,0.187188,0.079003),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.272111,0.424200,-0.131681),TVektor(0.252478,0.250623,-0.050022),TVektor(0.152994,0.187188,-0.079003),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.337680,-0.429519,0.083157),TVektor(0.344078,-0.443089,-0.000000),TVektor(0.310967,-0.339132,0.025443),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.344078,-0.443089,-0.000000),TVektor(0.310967,-0.339132,-0.025443),TVektor(0.310967,-0.339132,0.025443),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.344078,-0.443089,-0.000000),TVektor(0.337680,-0.429519,-0.083157),TVektor(0.310967,-0.339132,-0.025443),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.425808,-0.299615,0.011734),TVektor(0.425808,-0.299616,0.036162),TVektor(0.310967,-0.339132,0.025443),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.310967,-0.339132,-0.025443),TVektor(0.425808,-0.299616,-0.036162),TVektor(0.425808,-0.299616,-0.011734),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.425808,-0.299615,0.011734),TVektor(0.310967,-0.339132,0.025443),TVektor(0.425808,-0.299616,-0.011734),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.310967,-0.339132,0.025443),TVektor(0.310967,-0.339132,-0.025443),TVektor(0.425808,-0.299616,-0.011734),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.526909,-0.217920,-0.000000),TVektor(0.481365,-0.211800,-0.079041),TVektor(0.307312,0.262038,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.526909,-0.217920,-0.000000),TVektor(0.425808,-0.299616,-0.011734),TVektor(0.481365,-0.211800,-0.079041),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.252478,0.250623,-0.050022),TVektor(0.292624,-0.233330,-0.079040),TVektor(0.152994,0.187188,-0.079003),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.425808,-0.299616,-0.036162),TVektor(0.310967,-0.339132,-0.025443),TVektor(0.292624,-0.233330,-0.079040),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.307312,0.262038,-0.000000),TVektor(0.252478,0.250623,-0.050022),TVektor(0.272111,0.424200,-0.131681),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.152994,0.187188,-0.079003),TVektor(0.292624,-0.233330,-0.079040),TVektor(0.037915,0.192898,-0.480456),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,-0.079040),TVektor(0.337680,-0.429519,-0.083157),TVektor(0.284918,-0.509264,-0.203515),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.133598,-0.251082,-0.420063),TVektor(0.292624,-0.233330,-0.079040),TVektor(0.211474,-0.572864,-0.315706),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.331535,-0.591320,-0.125056),TVektor(0.336669,-0.614172,-0.000000),TVektor(0.298595,-0.651036,-0.128792),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.331535,-0.591320,-0.125056),TVektor(0.298595,-0.651036,-0.128792),TVektor(0.284918,-0.509264,-0.203515),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.303728,-0.673891,-0.000000),TVektor(0.305688,-0.853222,-0.000000),TVektor(0.298595,-0.651036,-0.128792),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.211474,-0.572864,-0.315706),TVektor(0.284918,-0.509264,-0.203515),TVektor(0.298595,-0.651036,-0.128792),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.321691,0.438492,-0.000000),TVektor(0.175271,0.884169,-0.093984),TVektor(0.183311,0.896988,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.233807,-0.804031,-0.147786),TVektor(0.305688,-0.853222,-0.000000),TVektor(0.047299,-0.769636,-0.214821),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.175271,0.884169,-0.093984),TVektor(0.060328,0.781745,-0.441679),TVektor(-0.451100,1.188904,-0.083930),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.175271,0.884169,-0.093984),TVektor(0.201696,0.422484,-0.453494),TVektor(0.060328,0.781745,-0.441679),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.183311,0.896988,-0.000000),TVektor(0.175271,0.884169,-0.093984),TVektor(-0.451100,1.188904,-0.083930),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.037915,0.192898,-0.480456),TVektor(-0.368543,0.284194,-0.616184),TVektor(0.201696,0.422484,-0.453494),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.050755,-0.616432,-0.404977),TVektor(0.211474,-0.572864,-0.315706),TVektor(0.047299,-0.769636,-0.214821),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,-0.496902),TVektor(0.211474,-0.572864,-0.315706),TVektor(-0.050755,-0.616432,-0.404977),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.037915,0.192898,-0.480456),TVektor(-0.234983,-0.270325,-0.496902),TVektor(-0.368543,0.284194,-0.616184),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,-0.496902),TVektor(-0.356054,-0.441801,-0.499736),TVektor(-0.503386,-0.235333,-0.500551),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.225564,-0.612143,-0.400558),TVektor(-0.234983,-0.270325,-0.496902),TVektor(-0.050755,-0.616432,-0.404977),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.094870,-0.734971,-0.290978),TVektor(-0.225564,-0.612143,-0.400558),TVektor(0.047299,-0.769636,-0.214821),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.129157,-0.840458,-0.000000),TVektor(-0.018264,-0.831302,0.000000),TVektor(0.047299,-0.769636,-0.214821),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.429662,-1.055333,-0.267851),TVektor(-0.581950,-1.007189,-0.393724),TVektor(-0.356054,-0.441801,-0.499736),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.259712,-1.044447,0.000000),TVektor(-0.429662,-1.055333,-0.267851),TVektor(-0.287628,-0.826596,-0.202588),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.225564,-0.612143,-0.400558),TVektor(-0.094870,-0.734971,-0.290978),TVektor(-0.287628,-0.826596,-0.202588),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.259712,-1.044447,0.000000),TVektor(-0.219726,-0.859500,-0.133844),TVektor(-0.168691,-0.872945,0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.168691,-0.872945,0.000000),TVektor(-0.094870,-0.734971,-0.290978),TVektor(-0.018264,-0.831302,0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.287628,-0.826596,-0.202588),TVektor(-0.219726,-0.859500,-0.133844),TVektor(-0.259712,-1.044447,0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.526909,-0.217920,-0.000000),TVektor(0.307312,0.262038,-0.000000),TVektor(0.481365,-0.211800,0.079041),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.481365,-0.211800,0.079041),TVektor(0.425808,-0.299616,0.036162),TVektor(0.425808,-0.299616,0.011734),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.252478,0.250623,0.050021),TVektor(0.152994,0.187188,0.079003),TVektor(0.292624,-0.233330,0.079040),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.425808,-0.299616,0.036162),TVektor(0.292624,-0.233330,0.079040),TVektor(0.310967,-0.339132,0.025443),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.307312,0.262038,-0.000000),TVektor(0.272111,0.424200,0.131681),TVektor(0.252478,0.250623,0.050021),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.152994,0.187188,0.079003),TVektor(0.037915,0.192898,0.480456),TVektor(0.292624,-0.233330,0.079040),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,0.079040),TVektor(0.284918,-0.509264,0.203515),TVektor(0.337680,-0.429519,0.083157),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.133598,-0.251082,0.420063),TVektor(0.211474,-0.572864,0.315706),TVektor(0.292624,-0.233330,0.079040),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.331535,-0.591320,0.125056),TVektor(0.298595,-0.651036,0.128792),TVektor(0.336669,-0.614172,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.331535,-0.591320,0.125056),TVektor(0.284918,-0.509264,0.203515),TVektor(0.298595,-0.651036,0.128792),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.303728,-0.673891,-0.000000),TVektor(0.298595,-0.651036,0.128792),TVektor(0.305688,-0.853222,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.211474,-0.572864,0.315706),TVektor(0.233807,-0.804031,0.147786),TVektor(0.298595,-0.651036,0.128792),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.321691,0.438492,-0.000000),TVektor(0.175271,0.884169,0.093984),TVektor(0.272111,0.424200,0.131681),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.233807,-0.804031,0.147786),TVektor(0.047299,-0.769636,0.214821),TVektor(0.305688,-0.853222,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.175271,0.884169,0.093984),TVektor(-0.508512,1.022462,0.468151),TVektor(0.060328,0.781745,0.441679),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.175271,0.884169,0.093984),TVektor(0.060328,0.781745,0.441679),TVektor(0.201696,0.422484,0.453494),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.183311,0.896988,-0.000000),TVektor(-0.451100,1.188904,0.083930),TVektor(0.175271,0.884169,0.093984),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.037915,0.192898,0.480456),TVektor(-0.508512,1.022462,0.468151),TVektor(-0.368543,0.284194,0.616184),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.050755,-0.616432,0.404977),TVektor(0.047299,-0.769636,0.214821),TVektor(0.211474,-0.572864,0.315706),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,0.496902),TVektor(0.211474,-0.572864,0.315706),TVektor(0.133598,-0.251082,0.420063),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.037915,0.192898,0.480456),TVektor(-0.368543,0.284194,0.616184),TVektor(-0.234983,-0.270325,0.496902),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,0.496902),TVektor(-0.503386,-0.235333,0.500551),TVektor(-0.356054,-0.441801,0.499736),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.225564,-0.612143,0.400558),TVektor(-0.234983,-0.270325,0.496902),TVektor(-0.356054,-0.441801,0.499736),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.094870,-0.734971,0.290978),TVektor(0.047299,-0.769636,0.214821),TVektor(-0.225564,-0.612143,0.400558),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.129157,-0.840458,-0.000000),TVektor(0.047299,-0.769636,0.214821),TVektor(-0.018264,-0.831302,0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.429662,-1.055333,0.267851),TVektor(-0.356054,-0.441801,0.499736),TVektor(-0.581950,-1.007189,0.393724),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.259712,-1.044447,0.000000),TVektor(-0.287628,-0.826596,0.202588),TVektor(-0.429662,-1.055333,0.267851),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.225564,-0.612143,0.400558),TVektor(-0.287628,-0.826596,0.202588),TVektor(-0.094870,-0.734971,0.290978),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.259712,-1.044447,0.000000),TVektor(-0.168691,-0.872945,0.000000),TVektor(-0.219726,-0.859500,0.133844),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.168691,-0.872945,0.000000),TVektor(-0.094870,-0.734971,0.290978),TVektor(-0.219726,-0.859500,0.133844),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.287628,-0.826596,0.202588),TVektor(-0.259712,-1.044447,0.000000),TVektor(-0.219726,-0.859500,0.133844),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,0.496902),TVektor(0.133598,-0.251082,0.420063),TVektor(0.037915,0.192898,0.480456),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.503386,-0.235333,0.500551),TVektor(-0.234983,-0.270325,0.496902),TVektor(-0.368543,0.284194,0.616184),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.201696,0.422484,0.453494),TVektor(0.272111,0.424200,0.131681),TVektor(0.175271,0.884169,0.093984),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.508512,1.022462,0.468151),TVektor(0.201696,0.422484,0.453494),TVektor(0.060328,0.781745,0.441679),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.201696,0.422484,0.453494),TVektor(-0.508512,1.022462,0.468151),TVektor(0.037915,0.192898,0.480456),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.508512,1.022462,0.468151),TVektor(0.175271,0.884169,0.093984),TVektor(-0.451100,1.188904,0.083930),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.175271,0.884169,-0.093984),TVektor(0.321691,0.438492,-0.000000),TVektor(0.272111,0.424200,-0.131681),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.451100,1.188904,-0.083930),TVektor(-0.450086,1.208294,0.000000),TVektor(0.183311,0.896988,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.451100,1.188904,0.083930),TVektor(0.183311,0.896988,-0.000000),TVektor(-0.450086,1.208294,0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.201696,0.422484,-0.453494),TVektor(-0.368543,0.284194,-0.616184),TVektor(0.060328,0.781745,-0.441679),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.060328,0.781745,-0.441679),TVektor(-0.368543,0.284194,-0.616184),TVektor(-0.508512,1.022462,-0.468151),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.451100,1.188904,-0.083930),TVektor(0.060328,0.781745,-0.441679),TVektor(-0.508512,1.022462,-0.468151),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.175271,0.884169,0.093984),TVektor(0.321691,0.438492,-0.000000),TVektor(0.183311,0.896988,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.201696,0.422484,-0.453494),TVektor(0.175271,0.884169,-0.093984),TVektor(0.272111,0.424200,-0.131681),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.272111,0.424200,0.131681),TVektor(0.307312,0.262038,-0.000000),TVektor(0.321691,0.438492,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,-0.496902),TVektor(0.037915,0.192898,-0.480456),TVektor(0.133598,-0.251082,-0.420063),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.503386,-0.235333,-0.500551),TVektor(-0.368543,0.284194,-0.616184),TVektor(-0.234983,-0.270325,-0.496902),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.272111,0.424200,-0.131681),TVektor(0.321691,0.438492,-0.000000),TVektor(0.307312,0.262038,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.287628,-0.826596,-0.202588),TVektor(-0.356054,-0.441801,-0.499736),TVektor(-0.225564,-0.612143,-0.400558),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.356054,-0.441801,-0.499736),TVektor(-0.287628,-0.826596,-0.202588),TVektor(-0.429662,-1.055333,-0.267851),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.356054,-0.441801,-0.499736),TVektor(-0.581950,-1.007189,-0.393724),TVektor(-0.503386,-0.235333,-0.500551),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.429662,-1.055333,0.267851),TVektor(-0.225564,-0.612143,0.400558),TVektor(-0.356054,-0.441801,0.499736),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.225564,-0.612143,0.400558),TVektor(-0.429662,-1.055333,0.267851),TVektor(-0.287628,-0.826596,0.202588),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.581950,-1.007189,0.393724),TVektor(-0.356054,-0.441801,0.499736),TVektor(-0.503386,-0.235333,0.500551),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.094870,-0.734971,-0.290978),TVektor(-0.168691,-0.872945,0.000000),TVektor(-0.219726,-0.859500,-0.133844),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.094870,-0.734971,0.290978),TVektor(-0.168691,-0.872945,0.000000),TVektor(-0.018264,-0.831302,0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.287628,-0.826596,-0.202588),TVektor(-0.094870,-0.734971,-0.290978),TVektor(-0.219726,-0.859500,-0.133844),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.094870,-0.734971,0.290978),TVektor(-0.287628,-0.826596,0.202588),TVektor(-0.219726,-0.859500,0.133844),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.047299,-0.769636,-0.214821),TVektor(0.211474,-0.572864,-0.315706),TVektor(0.233807,-0.804031,-0.147786),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.047299,-0.769636,-0.214821),TVektor(-0.018264,-0.831302,0.000000),TVektor(-0.094870,-0.734971,-0.290978),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.225564,-0.612143,0.400558),TVektor(0.047299,-0.769636,0.214821),TVektor(-0.050755,-0.616432,0.404977),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.305688,-0.853222,-0.000000),TVektor(0.298595,-0.651036,0.128792),TVektor(0.233807,-0.804031,0.147786),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.047299,-0.769636,-0.214821),TVektor(0.305688,-0.853222,-0.000000),TVektor(0.129157,-0.840458,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.298595,-0.651036,-0.128792),TVektor(0.233807,-0.804031,-0.147786),TVektor(0.211474,-0.572864,-0.315706),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.211474,-0.572864,0.315706),TVektor(0.047299,-0.769636,0.214821),TVektor(0.233807,-0.804031,0.147786),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.047299,-0.769636,-0.214821),TVektor(-0.225564,-0.612143,-0.400558),TVektor(-0.050755,-0.616432,-0.404977),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.018264,-0.831302,0.000000),TVektor(0.047299,-0.769636,0.214821),TVektor(-0.094870,-0.734971,0.290978),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.298595,-0.651036,-0.128792),TVektor(0.305688,-0.853222,-0.000000),TVektor(0.233807,-0.804031,-0.147786),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.298595,-0.651036,0.128792),TVektor(0.284918,-0.509264,0.203515),TVektor(0.211474,-0.572864,0.315706),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.305688,-0.853222,-0.000000),TVektor(0.047299,-0.769636,0.214821),TVektor(0.129157,-0.840458,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,0.496902),TVektor(-0.225564,-0.612143,0.400558),TVektor(-0.050755,-0.616432,0.404977),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.211474,-0.572864,0.315706),TVektor(-0.234983,-0.270325,0.496902),TVektor(-0.050755,-0.616432,0.404977),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,0.079040),TVektor(0.211474,-0.572864,0.315706),TVektor(0.284918,-0.509264,0.203515),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,0.079040),TVektor(0.037915,0.192898,0.480456),TVektor(0.133598,-0.251082,0.420063),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.336669,-0.614172,-0.000000),TVektor(0.298595,-0.651036,0.128792),TVektor(0.303728,-0.673891,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.307312,0.262038,-0.000000),TVektor(0.481365,-0.211800,-0.079041),TVektor(0.252478,0.250623,-0.050022),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.481365,-0.211800,0.079041),TVektor(0.307312,0.262038,-0.000000),TVektor(0.252478,0.250623,0.050021),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.425808,-0.299616,-0.011734),TVektor(0.425808,-0.299616,-0.036162),TVektor(0.481365,-0.211800,-0.079041),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.298595,-0.651036,-0.128792),TVektor(0.336669,-0.614172,-0.000000),TVektor(0.303728,-0.673891,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.425808,-0.299616,0.011734),TVektor(0.526909,-0.217920,-0.000000),TVektor(0.481365,-0.211800,0.079041),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.337680,-0.429519,0.083157),TVektor(0.310967,-0.339132,0.025443),TVektor(0.292624,-0.233330,0.079040),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.337680,-0.429519,-0.083157),TVektor(0.292624,-0.233330,-0.079040),TVektor(0.310967,-0.339132,-0.025443),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.211474,-0.572864,-0.315706),TVektor(0.292624,-0.233330,-0.079040),TVektor(0.284918,-0.509264,-0.203515),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.211474,-0.572864,-0.315706),TVektor(-0.234983,-0.270325,-0.496902),TVektor(0.133598,-0.251082,-0.420063),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.037915,0.192898,-0.480456),TVektor(0.292624,-0.233330,-0.079040),TVektor(0.133598,-0.251082,-0.420063),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,0.079040),TVektor(0.481365,-0.211800,0.079041),TVektor(0.252478,0.250623,0.050021),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,0.079040),TVektor(0.425808,-0.299616,0.036162),TVektor(0.481365,-0.211800,0.079041),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,-0.079040),TVektor(0.252478,0.250623,-0.050022),TVektor(0.481365,-0.211800,-0.079041),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.292624,-0.233330,-0.079040),TVektor(0.481365,-0.211800,-0.079041),TVektor(0.425808,-0.299616,-0.036162),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(-0.234983,-0.270325,-0.496902),TVektor(-0.225564,-0.612143,-0.400558),TVektor(-0.356054,-0.441801,-0.499736),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.526909,-0.217920,-0.000000),TVektor(0.425808,-0.299615,0.011734),TVektor(0.425808,-0.299616,-0.011734),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.425808,-0.299616,0.011734),TVektor(0.425808,-0.299615,-0.011734),TVektor(0.526909,-0.217920,-0.000000),mtl_haut);
        szene->dreieckHinzufuegen(TVektor(0.152994,0.187188,0.079003),TVektor(0.201696,0.422484,0.453494),TVektor(0.037915,0.192898,0.480456),mtl_Rot);
        szene->dreieckHinzufuegen(TVektor(0.152994,0.187188,-0.079003),TVektor(0.037915,0.192898,-0.480456),TVektor(0.201696,0.422484,-0.453494),mtl_Rot);
        szene->dreieckHinzufuegen(TVektor(0.201696,0.422484,-0.453494),TVektor(0.272111,0.424200,-0.131681),TVektor(0.152994,0.187188,-0.079003),mtl_Rot);
        szene->dreieckHinzufuegen(TVektor(0.272111,0.424200,0.131681),TVektor(0.201696,0.422484,0.453494),TVektor(0.152994,0.187188,0.079003),mtl_Rot);
        szene->dreieckHinzufuegen(TVektor(0.284918,-0.509264,-0.203515),TVektor(0.337680,-0.429519,-0.083157),TVektor(0.279741,-0.536108,-0.088780),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.286137,-0.536655,-0.000000),TVektor(0.279741,-0.536108,-0.088780),TVektor(0.344078,-0.443089,-0.000000),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.279741,-0.536108,-0.088780),TVektor(0.331535,-0.591320,-0.125056),TVektor(0.284918,-0.509264,-0.203515),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.286137,-0.536655,-0.000000),TVektor(0.336669,-0.614172,-0.000000),TVektor(0.279741,-0.536108,-0.088780),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.284918,-0.509264,0.203515),TVektor(0.279742,-0.536108,0.088780),TVektor(0.337680,-0.429519,0.083157),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.286137,-0.536655,-0.000000),TVektor(0.344078,-0.443089,-0.000000),TVektor(0.279742,-0.536108,0.088780),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.279742,-0.536108,0.088780),TVektor(0.284918,-0.509264,0.203515),TVektor(0.331535,-0.591320,0.125056),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.286137,-0.536655,-0.000000),TVektor(0.279742,-0.536108,0.088780),TVektor(0.336669,-0.614172,-0.000000),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.279742,-0.536108,0.088780),TVektor(0.344078,-0.443089,-0.000000),TVektor(0.337680,-0.429519,0.083157),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.336669,-0.614172,-0.000000),TVektor(0.279742,-0.536108,0.088780),TVektor(0.331535,-0.591320,0.125056),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.344078,-0.443089,-0.000000),TVektor(0.279741,-0.536108,-0.088780),TVektor(0.337680,-0.429519,-0.083157),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(0.279741,-0.536108,-0.088780),TVektor(0.336669,-0.614172,-0.000000),TVektor(0.331535,-0.591320,-0.125056),mtl_dunkelrot);
        szene->dreieckHinzufuegen(TVektor(3.174232,-3.174233,1.130244),TVektor(-3.174233,3.174234,1.130245),TVektor(-3.174233,-3.174232,1.130245),mtl_spiegel);
        szene->dreieckHinzufuegen(TVektor(3.174232,-3.174233,1.130244),TVektor(3.174233,3.174232,1.130245),TVektor(-3.174233,3.174234,1.130245),mtl_spiegel);


    }

    void Init(){
        ProgrammName = "Einfacher Ray-Tracing Renderer";
        ProgrammInfo = "Simulation komplexer System WS21/22\nJoern Froboese\nKatja Ruge\nMaximilian Kens";

        InsertTaste(0, "Leer", "l�dt Leere Szene");
        InsertTaste(1, "Diamant", "l�dt Diamant Szene");
        InsertTaste(2, "Drei Kugeln", "l�dt Szene mit 3 Kugeln");
        InsertTaste(3, "Tunnel", "l�dt Tunnel Szene");
        InsertTaste(4, "Gesicht", "l�dt default Face Szene");
        InsertTaste(5, "Leer", "l�dt Leere Szene");



        // Diamant hinzufuegen
        //Diamant();
        Leer();



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

    void RunTaste0(){
        currenttile = 0;
        Clear();
        delete szene;
        delete kamera;
        Leer();
    }

    void RunTaste1(){
        currenttile = 0;
        Clear();
        delete szene;
        delete kamera;
        Diamant();
    }

    void RunTaste2(){
        currenttile = 0;
        Clear();
        delete szene;
        delete kamera;
        DreiKugeln();
    }

    void RunTaste3(){
        currenttile = 0;
        Clear();
        delete szene;
        delete kamera;
        Tunnel();
    }

    void RunTaste4(){
        currenttile = 0;
        Clear();
        delete szene;
        delete kamera;
        Face();
    }

    void RunTaste5(){
        currenttile = 0;
        Clear();
        delete szene;
        delete kamera;
        Leer();
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
