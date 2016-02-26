#include "element.h"
#include "plateau.h"

int main(){
	printf("initPlateau \n");
	plateau p = initPlateau(2, 3);
	printf("initElement \n");
	p->data[0][0] = initElement(vide);
	p->data[1][0] = initElement(snake);
	p->data[1][1] = initElement(mur);
	p->data[0][1] = initElement(snake);
	p->data[0][2] = initElement(mur);
	p->data[1][2] = initElement(mur);
	printf("showPlateau \n");
	showPlateau(p);
	getchar();
	return 0;
}