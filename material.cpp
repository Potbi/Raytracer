#include "material.h"

Material::Material (){
    this->farbe = Weiss;
	this->reflekt = 0;
}

Material::Material (TColor farbe, float reflekt){
    this->farbe = farbe;
	this->reflekt = reflekt;
}
