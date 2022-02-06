#ifndef DREIECK_H
#define DREIECK_H

#include "material.h"
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
		TVektor position;
        TVektor normal;
		Material material;

		// Konstruktoren
		Dreieck ();
		Dreieck (TVektor punktA, TVektor punktB, TVektor punktC, Material material);

		//Methoden
		Strahl schnitt(Strahl s);
		Dreieck& operator=(Dreieck d);
};

#endif