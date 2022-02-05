#ifndef LICHT_H
#define LICHT_H

#include "plan.h"

class Licht{
private:

public:
    // Member-Variablen
    TVektor position;
	float helligkeit;
    
    // Konstruktoren
    Licht();
	Licht(TVektor position, float helligkeit);
};


#endif