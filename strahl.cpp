#include "strahl.h"
//#include <limits>

Strahl::Strahl(){
    TVektor null(3);
    this->ursprung = null;
    this->richtung = null;
    this->entfernung = NULL;
    this->schnittpunkt = null;
    this->normale = null;

}

Strahl::Strahl(TVektor ursprung, TVektor richtung){
	this->ursprung = ursprung;
	this->richtung = richtung;
    this->entfernung = NULL;
    this->schnittpunkt = NULL;
    this->normale = NULL;
}

Strahl Strahl:: operator=(Strahl s){
    Strahl s2(s.ursprung, s.richtung);
    s2.entfernung = s.entfernung;
    s2.schnittpunkt = s.schnittpunkt;
    s2.normale = s.normale;
    return s2;
}


