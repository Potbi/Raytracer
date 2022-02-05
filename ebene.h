#ifndef EBENE_H
#define EBENE_H

#include "strahl.h"
#include "material.h"
#include "plan.h"
#include "primitiv.h"

class Ebene : public Primitiv{
private:
	// Member-Variablen
	TVektor normal;
	TMatrix transform;
	float kachelgroesse;
    Material materialA;
	Material materialB;

public:
    // Member-Variablen
    TVektor eckpunkt;
	TVektor a;
	TVektor b;
    float breite;
    float laenge;

    
    // Konstruktoren
    Ebene();
    Ebene(TVektor eckpunkt, TVektor a, TVektor b, float breite, float laenge, Material materialA, Material materialB);

    // Member-Funktionen
    Strahl schnitt(Strahl s);
};


#endif