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

	/*position p1 = cree_position(1, 1);
	serpent s = ajout_entete(NULL, p1);
	position p2 = cree_position(1, 2);
	s = ajout_entete(s, p2);
    position p3 = cree_position(1, 3);
    s = ajout_entete(s, p3);
    position p4 = cree_position(1, 4);
    s = ajout_entete(s, p4);
    position p5 = cree_position(1, 5);
    s = ajout_entete(s, p5);*/

    position pos1=cree_position(10,10);
	serpent s;
	/*s = ajout_entete(s,pos1);
	s = ajout_entete(s,pos2);
	s = ajout_entete(s,pos3);
	s = ajout_entete(s,pos4);
	s = ajout_entete(s,pos5);*/
	s = init_serpent(5,pos1,HAUT);

	addSerpentPlateau(s, p);
	showPlateau(p);

	/*position queue = get_position_queue(s);
	s = deplacement(BAS,s);
	updateSerpentPlateau(s,p,queue);
	showPlateau(p);*/

	getchar();
	return 0;
}
