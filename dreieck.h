#ifndef DREIECK_H
#define DREIECK_H

#include "strahl.h"
#include "material.h"
#include "plan.h"
#include "primitiv.h"

class Dreieck : public Primitiv {
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
        TVektor normal;

		// Konstruktoren
		Dreieck (TVektor punktA, TVektor punktB, TVektor punktC, Material material);
		Strahl schnitt(Strahl s);
};

#endif