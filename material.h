#ifndef MATERIAL_H
#define MATERIAL_H

#include "plan.h"

class Material {
	public:
        // Member-Variablen
        TColor farbe;
        float reflekt;
        float emission;


        // Konstruktoren
        Material();
        Material(TColor farbe, float reflekt, float emission);


};
#endif



