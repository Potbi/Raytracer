#ifndef KAMERA_H
#define KAMERA_H

#include "strahl.h"
#include "plan.h"

TVektor Kreuzprodukt(TVektor a, TVektor b){
//Kreuzprodukt der Vektoren a und b berechnen.
TVektor c;
c = TVektor(
    a[1]*b[2]-a[2]*b[1],
    a[2]*b[0]-a[0]*b[2],
    a[0]*b[1]-a[1]*b[0]
    );
return c;
}

class Kamera {
public:
    // Member-Variablen
    TVektor position;
    TVektor rechts;
    TVektor oben;
    TVektor blick;

    int aufloesungX;
    int aufloesungY;
    float brennweite;


    // Konstruktoren
    Kamera();
    Kamera(TVektor position, TVektor blick, TVektor oben, int aufloesungX, int aufloesungY, float brennweite);

    // Member-Funktionen
    Strahl gibStrahl(int x,int y);
};

#endif
