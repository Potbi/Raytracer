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
    this->transform = TMatrix(2,3);
    this->transform(0,0) = this->a(0);
    this->transform(0,1) = this->a(1);
    this->transform(0,2) = this->a(2);
    this->transform(1,0) = this->b(0);
    this->transform(1,1) = this->b(1);
    this->transform(1,2) = this->b(2);


	//this->transform = TMatrix(this->a[0],this->b[0],this->normal[0],this->a[1],this->b[1],this->normal[1],this->a[2],this->b[2],this->normal[2]);


	// Ruecktransformation Welt -> Ebene
	//this->transform = this->transform^"t";
	// z-Koordinate ist fuer Punkte in der Ebene 0 (dritte Zeile nicht benoetigt)
	//this->transform.Resize(2,3);
	this->kachelgroesse = 0.5;
}


Strahl Ebene::schnitt(Strahl s){
	EinheitsVektor(s.richtung);
    float zaehler = -((s.ursprung-this->eckpunkt)*this->normal);
    float nenner = (s.richtung*this->normal);
    // Schnittstrahl darf nicht parallel zur Ebene sein.
    if (nenner == 0){
        s.entfernung = -1;
		return(s);
    } else {
        // Schnittpunktberechnung mit Ebene.
        s.entfernung = zaehler/nenner;
        if (s.entfernung < 0){
			// Schnittpunkte, die in negative Strahlrichtung liegen, werden ignoriert.
            s.entfernung = -1;
			return(s);
        } else {
            // Berechne Koordinaten des Schnittpunkts (in Weltkoordinaten).
            s.schnittpunkt = TVektor(s.ursprung + s.entfernung * s.richtung);
			// Transformation auf Ebenen-Koordinaten.
			TVektor inEbene = this->transform * (s.schnittpunkt-this->eckpunkt);
			if ((inEbene[0] < breite) && (inEbene[0] > 0) && (inEbene[1] > 0) && (inEbene[1] < laenge)){
				s.normale = this->normal;
				this->material = ((((int)(inEbene[0]/this->kachelgroesse) % 2) == ((int)(inEbene[1]/this->kachelgroesse) % 2)) ? materialA : materialB);
                //this->material = materialA;
                return(s);
			} else {
				s.entfernung = -1;
				return(s);
			}
		}
	}			
}

float abs(float zahl){
    return((zahl > 0) ? zahl : -zahl);
}

