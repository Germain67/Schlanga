#include "element.h"
#include "snake.h"
#include "plateau.h"

element initElement(typeCase t){
	element e = (element) malloc(sizeof(element));
	e->type = t;
	return e;
}

