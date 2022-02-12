#include "licht.h"
#include <iostream>

Licht::Licht(){
    this->position = NULL;
    this->radius = 0;
}

Licht::Licht(TVektor position, float radius){
    this->position = position;
    this->radius = radius;
}


Strahl Licht::schnitt(Strahl s){
    EinheitsVektor(s.richtung);
    if (Norm(s.richtung)==0){
        // Richtung des Schnittstrahls darf nicht 0 sein.
        s.entfernung = -1;
        return(s);
    }
    else {
        // quadratische Gleichung loesen
        float p = 2 * (s.richtung*(s.ursprung - this->position)) / (s.richtung * s.richtung);
        float q = ((s.ursprung - this->position) * (s.ursprung - this->position) - (this->radius * this->radius)) / (s.richtung * s.richtung);

        // Fallunterscheidung Wurzelterm
        float diskriminante = (p*p)/4 - q;
        if (diskriminante < 0) {
            s.entfernung = -1;
            return(s);
        }
        if (diskriminante >= 0) {
            float t1 = -p/2 + sqrt(diskriminante);
            float t2 = -p/2 - sqrt(diskriminante);
            s.entfernung = ((abs(t1) < abs(t2)) ? t1 : t2);
            s.schnittpunkt = s.ursprung + s.richtung*s.entfernung;
            s.normale = s.schnittpunkt - this->position;
            EinheitsVektor(s.normale);
        }
    }
    return s;
}


