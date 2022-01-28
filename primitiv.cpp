#include "primitiv.h"


Primitiv::Primitiv(TVektor position, Material material, float radius){
	this->kugel = Kugel(position, material, radius);
    this->typ = true;
}

Strahl Primitiv::schnitt(Strahl s){
    if (typ == true){
        return kugel.schnitt(s);
    }
    else{
        // hier muss dann das dreieck rein
    }
    
}

Material Primitiv::getMaterial(){
    if (typ == true){
        return kugel.material;
    }
    else{
        // hier muss dann das dreieck rein
    }
}

TVektor Primitiv::getPosition(){
    if (typ == true){
        return kugel.position;
    }
    else{
        // hier muss dann das dreieck rein
    }
}