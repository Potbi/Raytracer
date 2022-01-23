#ifndef KUGEL_H
#define KUGEL_H

#include "strahl.h"
#include "plan.h"

class Kugel{
private:

public:
    // Member-Variablen
    TVektor position;
    float radius;
    TColor farbe;
    
    // Konstruktoren
    Kugel();
    Kugel(TVektor position, TColor farbe, float radius);
    Kugel(float x, float y, float z, TColor farbe, float radius);

    // Member-Funktionen
    float schnitt(Strahl s);
};

#endif
