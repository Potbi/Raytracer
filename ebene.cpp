#include "ebene.h"
#include <iostream>

TVektor cross(TVektor a, TVektor b){
	return TVektor(a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]);
}

Ebene::Ebene(TVektor eckpunkt, TVektor a, TVektor b, float breite, float laenge, Material materialA, Material materialB){
    // Konstruktor 
	this->eckpunkt = eckpunkt;
	this->a = a;
	this->b = b;
	this->breite = breite;
	this->laenge = laenge;
	this->materialA = materialA;
	this->materialB = materialB;
	// Initialisieren von a, b, normal, transform
	EinheitsVektor(this->a);
	this->normal = cross(this->a,this->b);
	EinheitsVektor(this->normal);
	this->b = cross(this->normal,this->a);
	EinheitsVektor(this->b);
	// Transformationsmatrix von Ebene -> Welt
	this->transform = 	TMatrix(this->a[0],this->b[0],this->normal[0],
								this->a[1],this->b[1],this->normal[1],
								this->a[2],this->b[2],this->normal[2]);
	// die Ruecktransformation (Welt -> Ebene) ist die Transponierte
	this->transform = this->transform^"t";
	// z-Koordinate ist fuer Punkte in der Ebene 0 (dritte Zeile nicht benoetigt)
	this->transform.Resize(2,3);
	this->kachelgroesse = 2;
}


Strahl Ebene::schnitt(Strahl s){
	Strahl ergebnis;
	EinheitsVektor(s.richtung);
    float zaehler = -((s.ursprung-this->eckpunkt)*this->normal);
    float nenner = (s.richtung*this->normal);
    // Schnittstrahl darf nicht parallel zur Ebene sein.
    if (nenner == 0){
        ergebnis.entfernung = -1;
		return(ergebnis);
    } else {
        // Schnittpunktberechnung mit Ebene.
        ergebnis.entfernung = zaehler/nenner;
        if (ergebnis.entfernung < 0){
			// Schnittpunkte, die in negative Strahlrichtung liegen, werden ignoriert.
            ergebnis.entfernung = -1;
			return(ergebnis);
        } else {
            // Berechne Koordinaten des Schnittpunkts (in Weltkoordinaten).
            ergebnis.schnittpunkt = TVektor(s.ursprung + ergebnis.entfernung * s.richtung);
			// Transformation auf Ebenen-Koordinaten.
			TVektor inEbene = this->transform * ergebnis.schnittpunkt;
			if ((inEbene[0] < breite) && (inEbene[1] < laenge)){
				ergebnis.normale = this->normal;
				this->material = ((((int)inEbene[0]/kachelgroesse % 2) == ((int)inEbene[1]/kachelgroesse % 2)) ? materialA : materialB);
			} else {
				ergebnis.entfernung = -1;
				return(ergebnis);
			}
		}
	}			
}

float abs(float zahl){
    return((zahl > 0) ? zahl : -zahl);
}

