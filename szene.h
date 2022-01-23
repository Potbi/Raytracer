#ifndef SZENE_H
#define SZENE_H

#include "kugel.h"
#include <vector>


class Szene {
	public:
		// Member-Variablen
                int anzObjekte;
                std::vector<Kugel*> objekte;

                TColor hintergrund;

		// Konstruktoren
		Szene() {
                anzObjekte = 0;
                hintergrund = TColor(Schwarz);
                }

		// Member-Funktionen
		void kugelHinzufuegen (TVektor position, TColor farbe, float radius);
};
#endif


     
