#include "primitiv.h"


Primitiv::Primitiv(TVektor position, Material material, float radius){
	this->kugel = Kugel(position, material, radius);
    this->typ = true;
}
Primitiv::Primitiv(TVektor punktA, TVektor punktB, TVektor punktC, Material material){
    this->dreieck = Dreieck(punktA, punktB, punktC, material);
    this->typ = false;
}

Strahl Primitiv::schnitt(Strahl s){
    if (typ == true){
        return kugel.schnitt(s);
    }
    else{
        return dreieck.schnitt(s);
    }
    
}

Material Primitiv::getMaterial(){
    if (typ == true){
        return kugel.material;
    }
    else{
        return dreieck.material;
    }
}

TVektor Primitiv::getPosition(){
    if (typ == true){
        return kugel.position;
    }
    else{
        return dreieck.position;
    }
}