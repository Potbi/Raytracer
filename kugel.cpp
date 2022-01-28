#include "kugel.h"
#include <iostream>

Kugel::Kugel() {
    // Standardkonstruktor
    TVektor null(3);
    this->position = NULL;
    this->material = Material();
	//this->material = Material(Weiss,0.0,1.0);
	this->radius = 0;
}

Kugel::Kugel(TVektor position, Material material, float radius){
    // Konstruktor mit position als TVektor
	this->position = position;
	this->material = material;
	this->radius = radius;
}

Kugel::Kugel(float x, float y, float z, Material material, float radius){
    // Konstruktor mit position als Parameter x, y, z
	this->position = TVektor(x,y,z);
        this->material = material;
	this->radius = radius;
}

Strahl Kugel::schnitt(Strahl s){
    if (Norm(s.richtung)==0){
        // Richtung des Schnittstrahls darf nicht 0 sein.
        s.entfernung = -1;
    }
    else {
        // quadratische Gleichung l�sen
        float p = 2 * (s.richtung*(s.ursprung - this->position)) / (s.richtung * s.richtung);
        float q = ((s.ursprung - this->position) * (s.ursprung - this->position) - (this->radius * this->radius)) / (s.richtung * s.richtung);

        // Fallunterscheidung Wurzelterm
        float diskriminante = (p*p)/4 - q;
        if (diskriminante < 0)  s.entfernung = -1;
        if (diskriminante >= 0) {
            float t1 = -p/2 + sqrt(diskriminante);
            float t2 = -p/2 - sqrt(diskriminante);
            //ergebnis.position = s.position;
            //ergebnis.richtung = s.richtung;
            s.entfernung = ((abs(t1) < abs(t2)) ? t1 : t2);
            s.schnittpunkt = s.ursprung + s.richtung*s.entfernung;
            s.normale = s.schnittpunkt - this->position;
        }
    }

    return s;
}

float abs(float zahl){
    return((zahl > 0) ? zahl : -zahl);
}
