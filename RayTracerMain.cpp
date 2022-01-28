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
#include "material.h"

#include <time.h>

clock_t start, finish;

Kamera* kamera;
Szene* szene;

int totalpx;
int tilesize;
int currenttile;
int rows, columns;

class TUser : public TPlan {

    float cosBeta(TVektor a, TVektor b){
        // gibt einen Wert zwischen [0, 1] zur�ck
        // als Mass fuer den Winkel zwischen zwei Vektoren
        return std::max(0.0, ((a*b)/(sqrt(a*a)*sqrt(b*b))) );
        //return ((a*b)/(sqrt(a*a)*sqrt(b*b)));
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

        // ### PUNKTLICHT-SHADER ###
            if (szene.objekte[gewinner]->material.emission == 1){
                // reine Punktlichtquelle
            }

        // ### LAMBERTIAN SHADING ###
            TVektor lambertian;
            float beleuchtung = 0.1;
            Strahl lichtstrahl;

            // Lichtquellen suchen
            for(int i=0; i<szene.anzObjekte; i++){

                // Wenn Lichtquelle gefunden: ...
                if (szene.objekte[i]->material.emission > 0){
                    // ... -> Lichtstrahl von Objekt zur Lichtquelle berechnen
                    lichtstrahl.richtung = szene.objekte[i]->position - s_treffer.schnittpunkt;
                    EinheitsVektor(lichtstrahl.richtung);
                    lichtstrahl.ursprung = s_treffer.schnittpunkt + 0.01*lichtstrahl.richtung;

                    // Pruefen, ob Objekte im Weg sind
                    abstandMin  = std::numeric_limits<float>::infinity();
                    int gewinner_licht = -1;
                    for(int j=0; j<szene.anzObjekte; j++){

                        // den Lichtstrahl mit allen Objekten schneiden und Schnittinformationen speichern
                        lichtstrahl = szene.objekte[j]->schnitt(lichtstrahl);
                        if ((lichtstrahl.entfernung > 0)&&(lichtstrahl.entfernung < abstandMin)){
                            abstandMin=lichtstrahl.entfernung;
                            gewinner_licht = j;
                        }
                    }

                    // wenn die aktuell untersuchte Lichtquelle das nahste Objekt ist, dann beleuchtung ermitteln
                    if ((gewinner_licht >= 0) && (gewinner_licht == i)) {
                        beleuchtung += cosBeta(lichtstrahl.richtung, s_treffer.normale);
                    }
                }
            }


            int r = int(GetRValue(szene.objekte[gewinner]->material.farbe));
            int g = int(GetGValue(szene.objekte[gewinner]->material.farbe));
            int b = int(GetBValue(szene.objekte[gewinner]->material.farbe));
            if (beleuchtung > 1){beleuchtung = 1;}
            lambertian = TVektor(r,g,b) * beleuchtung;


            // ### REFLECTION SHADING ###
            TVektor reflection(0,0,0);
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
            return (reflection*ref_anteil + lambertian*(1.0-ref_anteil));
        }

        // Wenn kein Objekt geschnitten wurde, Hintergrundfarbe zurueckgeben.
        TColor hintergrund = hintergrundFarbe(s.richtung[2],-1,1);
        return TVektor(GetRValue(hintergrund),GetGValue(hintergrund),GetBValue(hintergrund));
    }

    float map(float x, float start1, float stop1, float start2, float stop2){
        return(start2+((x-start1)/(stop1-start1))*(stop2-start2));
    }

    TColor hintergrundFarbe(float x, float start, float stop){
        int r = (int)(map(x,start,stop,255,200)*100.0/255);          // 20
        int g = (int)(map(x,start,stop,255,200)*100.0/255);         // 100
        int b = (int)(map(x,start,stop,255,200)*100.0/255);         // 200
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
        Material mtl_leuchte2(Weiss, 0, 0.3);
        szene->kugelHinzufuegen(TVektor(0,-3,0), mtl_s, 1);
        szene->kugelHinzufuegen(TVektor(0,3,0), mtl_s, 1);
        szene->kugelHinzufuegen(TVektor(0,-3,5), mtl_leuchte, 0.1);
        szene->kugelHinzufuegen(TVektor(0,3,5), mtl_leuchte2, 0.1);
        szene->kugelHinzufuegen(TVektor(0,0,0), mtl_rot, 1);
        szene->kugelHinzufuegen(TVektor(0,0,2), mtl_rot, 0.4);


        std::cout<<szene->objekte[1]->radius;
        // Einstellungen f�r Kachel-Rendern.
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
