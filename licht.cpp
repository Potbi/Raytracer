#include "licht.h"
#include <iostream>

Licht::Licht(){
    this->position = NULL;
    this->helligkeit = 0;
}

Licht::Licht(TVektor position, float helligkeit, float radius){
    this->position = position;
    this->helligkeit = helligkeit;
    this->radius = radius;
}

float cosBeta(TVektor a, TVektor b){
    // gibt einen Wert zwischen [0, 1] zurueck
    // als Mass fuer den Winkel zwischen zwei Vektoren
    return std::max(0.0, ((a*b)/(sqrt(a*a)*sqrt(b*b))) );
}

TVektor Licht::leuchtbeitrag(Strahl s, float &entfernung){
    EinheitsVektor(s.richtung);
    if (Norm(s.richtung)==0){
        // Richtung des Schnittstrahls darf nicht 0 sein.
        entfernung = -1;
        return(TVektor(0,0,0));
    }
    else {
        // quadratische Gleichung loesen
        float p = 2 * (s.richtung*(s.ursprung - this->position)) / (s.richtung * s.richtung);
        float q = ((s.ursprung - this->position) * (s.ursprung - this->position) - (this->radius * this->radius)) / (s.richtung * s.richtung);

        // Fallunterscheidung Wurzelterm
        float diskriminante = (p*p)/4 - q;
        if (diskriminante < 0) {
            entfernung = -1;
            return(TVektor(0,0,0));
        }
        if (diskriminante >= 0) {
            float t1 = -p/2 + sqrt(diskriminante);
            float t2 = -p/2 - sqrt(diskriminante);
            entfernung = ((abs(t1) < abs(t2)) ? t1 : t2);
            TVektor schnittpunkt = s.ursprung + s.richtung*entfernung;
            TVektor normale = schnittpunkt - this->position;
            return ( (1-sqrt(1-pow((cosBeta((-1)*s.richtung,normale)),2))) * TVektor(255,255,255) );
        }
    }
}
