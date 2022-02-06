#ifndef PRIMITIV_H
#define PRIMITIV_H

//#include "dreieck.h"
//#include "kugel.h"
#include "material.h"
#include "strahl.h"
#include "plan.h"

class Primitiv{
private:

public:
    // Member-Variablen
    //Kugel kugel;
    //Dreieck dreieck;
    TVektor position;
	Material material;
    // Konstruktoren
    //Primitiv();
    //Primitiv(Material material);
    // Member-Funktionen
    virtual Strahl schnitt(Strahl s) = 0;
    //virtual Material getMaterial();
    //virtual TVektor getPosition();
};

#endif
