#include "szene.h"

void Szene::kugelHinzufuegen(TVektor position, Material material, float radius){
    objekte.push_back(new Kugel(position, material, radius));
    anzObjekte++;
}

void Szene::ebeneHinzufuegen (TVektor eckpunkt, TVektor a, TVektor b, float breite, float laenge, Material materialA, Material materialB){
    objekte.push_back(new Ebene(eckpunkt, a, b, breite, laenge, materialA, materialB));
    anzObjekte++;
}

void Szene::lichtHinzufuegen(TVektor position, float helligkeit, float radius){
    lichter.push_back(new Licht(position, helligkeit, radius));
    anzLichter++;
}

void Szene::dreieckHinzufuegen (TVektor punktA, TVektor punktB, TVektor punktC, Material material){
    objekte.push_back(new Dreieck(punktA, punktB, punktC, material));
    anzObjekte++;
}

void Szene::primitivHinzufuegen (Primitiv* primitiv){
    objekte.push_back(primitiv);
}

