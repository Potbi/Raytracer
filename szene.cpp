#include "szene.h"

void Szene::kugelHinzufuegen(TVektor position, Material material, float radius){
    objekte.push_back(new Kugel(position, material, radius));
    anzObjekte++;
}
void Szene::DreieckHinzufuegen(TVektor punktA, TVektor punktB, TVektor punktC, Material material){
    objekte.push_back(new Dreieck(punktA, punktB, punktC, material));
    anzObjekte++;
}

