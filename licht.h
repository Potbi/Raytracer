#ifndef LICHT_H
#define LICHT_H

#include "plan.h"
#include "strahl.h"

class Licht{
private:

public:
    // Member-Variablen
    TVektor position;
	float helligkeit;
    float radius;
    
    // Konstruktoren
    Licht();
	Licht(TVektor position, float helligkeit, float radius);
    TVektor leuchtbeitrag(Strahl s, float &entfernung);
};


#endif