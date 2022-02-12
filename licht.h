#ifndef LICHT_H
#define LICHT_H

#include "plan.h"
#include "strahl.h"

class Licht{
private:

public:
    // Member-Variablen
    TVektor position;
    float radius;
    
    // Konstruktoren
    Licht();
	Licht(TVektor position, float helligkeit, float radius);

    // Member-Funktionen
    Strahl schnitt(Strahl s);
};


#endif