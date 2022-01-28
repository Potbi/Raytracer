#include "dreieck.h"
#include <iostream>

TVektor cross(TVektor a, TVektor b){
	return TVektor(a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]);
}

Dreieck::Dreieck (TVektor punktA, TVektor punktB, TVektor punktC, TColor farbe){
	this->punktA = punktA;
	this->punktB = punktB;
	this->punktC = punktC;
	this->farbe = farbe;
    this->normal = cross(punktB-punktA,punktC-punktA);
    EinheitsVektor(this->normal);
    this->a = this->normal(0);
    this->b = this->normal(1);
    this->c = this->normal(2);
    this->d = this->normal * this->punktA;

}

float Dreieck::schnitt(Strahl s){
    EinheitsVektor(s.richtung);
    float zaehler = -((s.ursprung-this->punktA)*this->normal);
    float nenner = (s.richtung*this->normal);
    // Schnittstrahl darf nicht parallel zum Dreieck sein.
    if (nenner == 0){
        return -1;
    } else {
        // Schnittpunktberechnung mit Ebene.
        float t = zaehler/nenner;
        // Schnittpunkte, die in negative Strahlrichtung liegen, werden ignoriert.
        if (t < 0){
            return -1;
        // Pruefe, ob der Schnittpunkt im Dreieck liegt.
        } else {
            // Berechne Koordinaten des Schnittpunkts.
            TVektor schnittpunkt(s.ursprung + t * s.richtung);
            // https://math.stackexchange.com/questions/51326/determining-if-an-arbitrary-point-lies-inside-a-triangle-defined-by-three-points
            TVektor A = cross((this->punktB - this->punktA),(schnittpunkt - this->punktA));
            TVektor B = cross((this->punktC - this->punktB),(schnittpunkt - this->punktB));
            TVektor C = cross((this->punktA - this->punktC),(schnittpunkt - this->punktC));
            // Pruefe, ob alle Vektoren in die gleiche Richtung zeigen.
            if ( (Signum(A * this->normal) == Signum(B * this->normal)) && (Signum(A * this->normal) == Signum(C * this->normal)) ) {
                return t;
            } else {
                return -1;
            }
        }
    }
}

