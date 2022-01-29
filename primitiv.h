#ifndef PRIMITIV_H
#define PRIMITIV_H

#include "dreieck.h"
#include "kugel.h"
#include "material.h"
#include "strahl.h"
#include "plan.h"

class Primitiv{
private:

public:
    // Member-Variablen
    Kugel kugel;
    Dreieck dreieck;
    // typ ist true wenn Primitiv eine Kugel ist und false wenn es ein Dreieck ist
    bool typ;
    // Konstruktoren
    Primitiv(TVektor position, Material material, float radius);//Kugel
    Primitiv(TVektor punktA, TVektor punktB, TVektor punktC, Material material);//Dreieck
    //Primitiv(Material material);
    // Member-Funktionen
    Strahl schnitt(Strahl s);
    Material getMaterial();
    TVektor getPosition();
};

#endif
