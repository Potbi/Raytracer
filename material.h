#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>


class Material {
	public:
		// Member-Variablen
               TColor farbe;
               float reflekt;
               float emission;


		// Konstruktoren
               Material (TColor farbe, float reflekt, float emission);


};
#endif



