#ifndef MATERIAL_H
#define MATERIAL_H

#include "plan.h"

class Material {
	public:
		// Member-Variablen
        TColor farbe;
        float reflekt;


		// Konstruktoren
        Material();
        Material(TColor farbe, float reflekt);


};
#endif



