#ifndef SZENE_H
#define SZENE_H

#include "kugel.h"
#include "ebene.h"
#include "licht.h"
#include <vector>


class Szene {
	public:
		// Member-Variablen
                int anzObjekte;
                int anzLichter;
                std::vector<Primitiv*> objekte;
                std::vector<Licht*> lichter;

		// Konstruktoren
		Szene() {
                anzObjekte = 0;
                anzLichter = 0;
                }

		// Member-Funktionen
        void primitivHinzufuegen (Primitiv* primitiv);
		void kugelHinzufuegen (TVektor position, Material material, float radius);
        void ebeneHinzufuegen (TVektor eckpunkt, TVektor a, TVektor b, float breite, float laenge, Material materialA, Material materialB);
        void lichtHinzufuegen (TVektor position, float helligkeit, float radius);
};
#endif


     
