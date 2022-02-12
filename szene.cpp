#include "szene.h"
#include <iostream>

void Szene::kugelHinzufuegen(TVektor position, Material material, float radius){
    this->primitive.push_back(new Kugel(position, material, radius));
    this->anzPrimitive++;
}

void Szene::ebeneHinzufuegen (TVektor eckpunkt, TVektor a, TVektor b, float breite, float laenge, Material materialA, Material materialB, float kachelgroesse){
    this->primitive.push_back(new Ebene(eckpunkt, a, b, breite, laenge, materialA, materialB, kachelgroesse));
    this->anzPrimitive++;
}

void Szene::lichtHinzufuegen(TVektor position, float helligkeit, float radius){
    this->lichter.push_back(new Licht(position, helligkeit, radius));
    this->anzLichter++;
}

void Szene::dreieckHinzufuegen (TVektor punktA, TVektor punktB, TVektor punktC, Material material){
    this->primitive.push_back(new Dreieck(punktA, punktB, punktC, material));
    this->anzPrimitive++;
}

void Szene::primitivHinzufuegen (Primitiv* primitiv){
    this->primitive.push_back(primitiv);
    this->anzPrimitive++;
}

Szene::~Szene(){
    for(int i=0; i<this->anzLichter; i++){
        delete this->lichter[i];
    }
    for(int i=0; i<this->anzPrimitive; i++){
        delete this->primitive[i];
    }
}



