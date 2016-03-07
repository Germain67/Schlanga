#include "element.h"
#include "snake.h"
#include "plateau.h"

element initElement(typeCase t){
	element e = (element) malloc(sizeof(element));
	e->type = t;
	return e;
}

char caseSymbol(element elem){
	char symbol;
	if(elem->type == mur){
		symbol = '*';
	}
	else if(elem->type == vide){
    symbol = ' ';
	}
	else if(elem->type == snake){
		symbol = '0';
	}
	return symbol;
}

typeCase etat_case(plateau p, position pos) {
	typeCase res= ((p->data)[pos->x][pos->y])->type;
	return res;

}