#ifndef KUGEL_H
#define KUGEL_H


#include "strahl.h"
#include "plan.h"
#include "material.h"
#include "primitiv.h"

class Kugel:public Primitiv{
private:

public:
    // Member-Variablen
    float radius;
    
    // Konstruktoren
    Kugel();
    Kugel(TVektor position, Material material, float radius);
    Kugel(float x, float y, float z, Material material, float radius);

    // Member-Funktionen
    virtual Strahl schnitt(Strahl s);
    Kugel& operator=(Kugel k);
};

#endif
