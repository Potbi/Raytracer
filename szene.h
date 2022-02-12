#ifndef SZENE_H
#define SZENE_H

#include "kugel.h"
#include "ebene.h"
#include "dreieck.h"
#include "licht.h"
#include <vector>


class Szene {
	public:
		// Member-Variablen
                int anzPrimitive;
                int anzLichter;
                std::vector<Primitiv*> primitive;
                std::vector<Licht*> lichter;

		// Konstruktoren
		Szene() {
                anzPrimitive = 0;
                anzLichter = 0;
                }

        // Destruktoren
        ~Szene();

		// Member-Funktionen
        void primitivHinzufuegen (Primitiv* primitiv);
		void kugelHinzufuegen (TVektor position, Material material, float radius);
        void ebeneHinzufuegen (TVektor eckpunkt, TVektor a, TVektor b, float breite, float laenge, Material materialA, Material materialB, float kachelgroesse);
        void dreieckHinzufuegen (TVektor punktA, TVektor punktB, TVektor punktC, Material material);
        void lichtHinzufuegen (TVektor position, float helligkeit, float radius);
};
#endif


     
