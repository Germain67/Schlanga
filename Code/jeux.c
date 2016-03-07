#include "snake.h"
#include "element.h"
#include "plateau.h"
#include <stdio.h>
#include <stdlib.h>


void jeux(){
	plateau p = initPlateau(20, 20);
	initMurs(p);
	position pos = cree_position(10,10)
	serpent s = init_serpent(10, pos, HAUT);
	addSerpentPlateau(s, p);
	showPlateau(p);
	int dir = 8;
	position dir1 = HAUT;
	While (collision(p,dir1,s) == 0){
		scanf("%i", &dir);
		if (dir == 2){
			s = deplacement(BAS, s);
			dir1 = BAS;
		}
		if (dir == 8){
			s = deplacement(HAUT, s);
			dir1 = HAUT;
		}
		if (dir == 6){
			s = deplacement(DROITE, s);
			dir1 = DROITE;
		}
		if (dir == 4){
			s = deplacement(GAUCHE, s);
			dir1 = GAUCHE;
		}
		addSerpentPlateau(s, p);
		sshowPlateau(p);
	}
	printf("\n vous avez perdu", );
}
