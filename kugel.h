#ifndef KUGEL_H
#define KUGEL_H


#include "strahl.h"
#include "plan.h"
#include "material.h"
//#include "primitiv.h"

class Kugel{
private:

public:
    // Member-Variablen
    TVektor position;
    float radius;
    Material material;
    
    // Konstruktoren
    Kugel();
    Kugel(TVektor position, Material material, float radius);
    Kugel(float x, float y, float z, Material material, float radius);

    // Member-Funktionen
    Strahl schnitt(Strahl s);
    Kugel& operator=(Kugel k);
};

#endif
