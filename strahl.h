#ifndef STRAHL_H
#define STRAHL_H

#include "plan.h"

class Strahl {
public:
    // Member-Variablen
    TVektor ursprung;
    TVektor richtung;
    float entfernung;
    TVektor schnittpunkt;
    TVektor normale;

    // Konstruktoren
    Strahl();
    Strahl(TVektor ursprung, TVektor richtung);

    // Member-Funktionen
    Strahl operator=(Strahl s);

private:

};
#endif