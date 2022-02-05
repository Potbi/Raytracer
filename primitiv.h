#ifndef PRIMITIV_H
#define PRIMITIV_H

#include "material.h"
#include "strahl.h"

class Primitiv {
    // eine (abstrakte) Klasse mit der virtuellen Funktion "schnitt"
    public:
		Material material;
        virtual Strahl schnitt(Strahl s){};
};

#endif