#ifndef DREIECK_H
#define DREIECK_H

#include "strahl.h"
#include "plan.h"

class Dreieck{
	private:
		float a;
		float b;
		float c;
		float d;
	
	public:
		// Member-Variablen
		TVektor punktA;
		TVektor punktB;
		TVektor punktC;
		TColor farbe;
        TVektor normal;

		// Konstruktoren
		Dreieck (TVektor punktA, TVektor punktB, TVektor punktC, TColor farbe);
		float schnitt(Strahl s);
};

#endif