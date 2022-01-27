#include "material.h"

Material::Material (){
    this->farbe = Weiss;
	this->reflekt = 0;
	this->emission = 0;
}

Material::Material (TColor farbe, float reflekt, float emission){
    this->farbe = farbe;
	this->reflekt = reflekt;
	this->emission = emission;
}
