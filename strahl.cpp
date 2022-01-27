#include "strahl.h"
#include <iostream>
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

Strahl& Strahl::operator=(Strahl s){
    // Zuweisung durch Copy-and-Swap Mechanismus.
    std::swap(this->ursprung,s.ursprung);
    std::swap(this->richtung,s.richtung);
    std::swap(this->entfernung,s.entfernung);
    std::swap(this->schnittpunkt,s.schnittpunkt);
    std::swap(this->normale,s.normale);
    return *this;
}


