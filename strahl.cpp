#include "strahl.h"
//#include <limits>

Strahl::Strahl(){
    TVektor null(3);
    this->ursprung = null;
    this->richtung = null;
    this->entfernung = null;
    this->schnittpunkt = null;
    this->normale = null;

}

Strahl::Strahl(TVektor ursprung, TVektor richtung){
	this->ursprung = ursprung;
	this->richtung = richtung;
    this->entfernung = null;
    this->schnittpunkt = null;
    this->normale = null;
        
}


