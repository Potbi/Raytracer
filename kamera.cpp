#include "kamera.h"


Kamera::Kamera(){
    this->position = TVektor(0,0,0);
    this->blick = TVektor(1,0,0);
    this->oben = TVektor(0,0,1);
    this->rechts = Kreuzprodukt(blick, oben);
    EinheitsVektor(this->blick);
    EinheitsVektor(this->oben);
    EinheitsVektor(this->rechts);
    this->aufloesungX = 100;
    this->aufloesungY = 100;
    this->brennweite = 1;
}

Kamera::Kamera(TVektor position, TVektor blick, TVektor oben, int aufloesungX, int aufloesungY, float brennweite){
    this->position = position;
    this->blick = blick;
    this->oben = oben;
    this->rechts = Kreuzprodukt(blick, oben);
    EinheitsVektor(this->blick);
    EinheitsVektor(this->oben);
    EinheitsVektor(this->rechts);
    this->aufloesungX = aufloesungX;
    this->aufloesungY = aufloesungY;
    this->brennweite = brennweite;

}

Strahl Kamera::gibStrahl(int x,int y){
    TVektor richtung;
    double h_auslenkung, v_auslenkung, schrittweite;

    // Anpassung der Pixelposition so das der Koordinatenursprung in der Mitte liegt
    h_auslenkung = double(x) - double(aufloesungX)/2.0;
    v_auslenkung = double(y) - double(aufloesungY)/2.0;
    schrittweite = 2.0/double(aufloesungX);

    richtung = blick*brennweite + rechts*h_auslenkung*schrittweite + oben*v_auslenkung*schrittweite;
    EinheitsVektor(richtung);
    Strahl strahlObjekt(position, richtung);
    return strahlObjekt;
}
