#ifndef SZENE_H
#define SZENE_H

#include "primitiv.h"
#include "kugel.h"
#include <vector>


class Szene {
	public:
		// Member-Variablen
                int anzObjekte;
                std::vector<Primitiv> objekte;

                TColor hintergrund;

		// Konstruktoren
		Szene() {
                anzObjekte = 0;
                hintergrund = TColor(Schwarz);
                }

		// Member-Funktionen
		void kugelHinzufuegen (TVektor position, Material material, float radius);
};
#endif


     
