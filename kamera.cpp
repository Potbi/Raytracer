#include "kamera.h"


Kamera::Kamera(){
    this->position = NULL;
    this->blick = NULL;
    this->oben = NULL;
    this->rechts = NULL;
    this->aufloesungX = NULL;
    this->aufloesungY = NULL;
    this->brennweite = NULL;
}

Kamera::Kamera(TVektor position, TVektor blick, TVektor oben, int aufloesungX, int aufloesungY, float brennweite){
    this->position = position;
    this->blick = blick;
    this->oben = oben;
    this->rechts = Cross_product(blick, oben);
    EinheitsVektor(blick);
    EinheitsVektor(oben);
    EinheitsVektor(rechts);
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

    Strahl strahlObjekt(position, richtung);
    return strahlObjekt;
}