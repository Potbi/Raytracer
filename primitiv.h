#ifndef PRIMITIV_H
#define PRIMITIV_H

#include "material.h"
#include "strahl.h"
#include "plan.h"

class Primitiv{
private:

public:
    // Member-Variablen
    Material material;
    float radius;
    TVektor position;
    // Konstruktoren
    //Primitiv(Material material);
    // Member-Funktionen
    Strahl schnitt(Strahl s);
};

#endif
