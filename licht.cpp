#include "licht.h"

Licht::Licht(){
		this->position = NULL;
		this->helligkeit = 0;
}

Licht::Licht(TVektor position, float helligkeit){
		this->position = position;
		this->helligkeit = helligkeit;
}
