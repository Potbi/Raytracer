#include "kugel.h"
#include <iostream>

Kugel::Kugel() {
    // Standardkonstruktor
    TVektor null(3);
    this->position = null;
	this->farbe = Weiss;
	this->radius = 0;
}

Kugel::Kugel(TVektor position, TColor farbe, float radius){
    // Konstruktor mit position als TVektor
	this->position = position;
	this->farbe = farbe;
	this->radius = radius;
}

Kugel::Kugel(float x, float y, float z, TColor farbe, float radius){
    // Konstruktor mit position als Parameter x, y, z
	this->position = TVektor(x,y,z);
	this->farbe = farbe;
	this->radius = radius;
}

float Kugel::schnitt(Strahl s){
    if (Norm(s.richtung)==0){
        // Richtung des Schnittstrahls darf nicht 0 sein.
        return -1;
    } else {
        // quadratische Gleichung lösen
        float p = 2 * (s.richtung*(s.ursprung - this->position)) / (s.richtung * s.richtung);
        float q = ((s.ursprung - this->position) * (s.ursprung - this->position) - (this->radius * this->radius)) / (s.richtung * s.richtung);

        // Fallunterscheidung Wurzelterm
        float diskriminante = (p*p)/4 - q;
        if (diskriminante < 0)  return -1;
        if (diskriminante == 0) return -(p/2);
        if (diskriminante > 0) {
            float t1 = -p/2 + sqrt(diskriminante);
            float t2 = -p/2 - sqrt(diskriminante);
        return((abs(t1) < abs(t2)) ? t1 : t2);
        }
    }
}

float abs(float zahl){
    return((zahl > 0) ? zahl : -zahl);
}
