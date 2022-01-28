#include "szene.h"

void Szene::kugelHinzufuegen(TVektor position, Material material, float radius){
    objekte.push_back(Primitiv(position, material, radius));
    anzObjekte++;
}

