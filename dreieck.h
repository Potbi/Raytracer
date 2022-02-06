#ifndef DREIECK_H
#define DREIECK_H

#include "material.h"
#include "strahl.h"
#include "plan.h"
#include "primitiv.h"

class Dreieck:public Primitiv{
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
		Dreieck ();
		Dreieck (TVektor punktA, TVektor punktB, TVektor punktC, Material material);
		//Methoden
		virtual Strahl schnitt(Strahl s);
		Dreieck& operator=(Dreieck d);
};

#endif