#ifndef PRIMITIV_H
#define PRIMITIV_H

#include "kugel.h"
#include "material.h"
#include "strahl.h"
#include "plan.h"

class Primitiv{
private:

public:
    // Member-Variablen
    Kugel kugel;
    // typ ist true wenn Primitiv eine Kugel ist und false wenn es ein Dreieck ist
    bool typ;
    // Konstruktoren
    Primitiv(TVektor position, Material material, float radius);
    //Primitiv(Material material);
    // Member-Funktionen
    Strahl schnitt(Strahl s);
    Material getMaterial();
    TVektor getPosition();
};

#endif
