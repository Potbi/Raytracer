#include "szene.h"

void Szene::kugelHinzufuegen(TVektor position, TColor farbe, float radius){
    objekte.push_back(new Kugel(position, farbe, radius));
    anzObjekte++;
}

