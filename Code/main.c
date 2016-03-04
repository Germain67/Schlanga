#include "element.h"
#include "plateau.h"
#include "snake.h"
#include <stdlib.h>

void initMurs(plateau p){
	int x, y;
	for(x = 0; x < p->hauteur; x++){
		for(y = 0; y <p->largeur; y++){
			if(x == 0 || x == p->largeur - 1 || y == 0 || y == p->hauteur - 1){
				p->data[x][y] = initElement(mur);
			}
		}
	}
}

int main(){
	plateau p = initPlateau(20, 20);
	initMurs(p);
	position p1 = cree_position(1, 1);
	serpent s = init_serpent(NULL, p1);
	position p2 = cree_position(1, 2);
	s = ajout_entete(s, p2);

	printf("Vers le bas\n");	
	deplacement(BAS,s);
	deplacement(BAS,s);

	addSerpentPlateau(s, p);
	showPlateau(p);
	getchar();
	return 0;
}
