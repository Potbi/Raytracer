#include "dreieck.h"
#include <iostream>

TVektor cross(TVektor a, TVektor b){
	return TVektor(a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]);
}

Dreieck::Dreieck (){
    TVektor null(3);
	this->punktA = null;
	this->punktB = null;
	this->punktC = null;
	this->material = Material();
    this->normal = null;
    this->a = NULL;
    this->b = NULL;
    this->c = NULL;
    this->d = NULL;
    this->position = null;
}

Dreieck::Dreieck (TVektor punktA, TVektor punktB, TVektor punktC, Material material){
	this->punktA = punktA;
	this->punktB = punktB;
	this->punktC = punktC;
	this->material = material;
    this->normal = cross(punktB-punktA,punktC-punktA);
    EinheitsVektor(this->normal);
    this->a = this->normal(0);
    this->b = this->normal(1);
    this->c = this->normal(2);
    this->d = this->normal * this->punktA;
    this->position = (punktA+punktB+punktC)/3;

}

Strahl Dreieck::schnitt(Strahl s){
    EinheitsVektor(s.richtung);
    s.normale = normal;
    float zaehler = -((s.ursprung-this->punktA)*this->normal);
    float nenner = (s.richtung*this->normal);
    // Schnittstrahl darf nicht parallel zum Dreieck sein.
    if (nenner == 0){
        s.entfernung -1;
    } else {
        // Schnittpunktberechnung mit Ebene.
        float t = zaehler/nenner;
        // Schnittpunkte, die in negative Strahlrichtung liegen, werden ignoriert.
        if (t < 0){
            s.entfernung -1;
        // Pruefe, ob der Schnittpunkt im Dreieck liegt.
        } else {
            // Berechne Koordinaten des Schnittpunkts.
            TVektor schnittpunkt(s.ursprung + t * s.richtung);
            // schnittpunkt wird in dem strahl gespeichert
            s.schnittpunkt = schnittpunkt;
            // https://math.stackexchange.com/questions/51326/determining-if-an-arbitrary-point-lies-inside-a-triangle-defined-by-three-points
            TVektor A = cross((this->punktB - this->punktA),(schnittpunkt - this->punktA));
            TVektor B = cross((this->punktC - this->punktB),(schnittpunkt - this->punktB));
            TVektor C = cross((this->punktA - this->punktC),(schnittpunkt - this->punktC));
            // Pruefe, ob alle Vektoren in die gleiche Richtung zeigen.
            if ( (Signum(A * this->normal) == Signum(B * this->normal)) && (Signum(A * this->normal) == Signum(C * this->normal)) ) {
                s.entfernung = t;
            } else {
                s.entfernung = -1;
            }
        }
    }
    return s;
}


Dreieck& Dreieck::operator=(Dreieck d){
    // Zuweisung durch Copy-and-Swap Mechanismus.
    std::swap(this->punktA, d.punktA);
    std::swap(this->punktB, d.punktB);
    std::swap(this->punktC, d.punktC);
    std::swap(this->position, d.position);
    std::swap(this->material, d.material);
    std::swap(this->normal, d.normal);

    return *this;
}
