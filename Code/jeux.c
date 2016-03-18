#include "snake.h"
#include "element.h"
#include "plateau.h"
#include <stdio.h>
#include <stdlib.h>

void jeux(){
	int i;
	plateau p = initPlateau(20, 20);
	initMurs(p);
	position pos = cree_position(10,10);
	serpent s = init_serpent(5, pos, HAUT);
	addSerpentPlateau(s, p);
	showPlateau(p);
	int dir = 8;
	direction dir1 = HAUT;
	int b = 0;
	while (b == 0){
		position queue = get_position_queue(s);
		scanf("%d", &dir);
		if (dir == 2){
			dir1 = BAS;
		}
		if (dir == 8){
			dir1 = HAUT;
		}
		if (dir == 6){
			dir1 = DROITE;
		}
		if (dir == 4){
			dir1 = GAUCHE;
		}
		if (collision(p,dir1,s) == 1){
			b = 1;
		}
		s = deplacement(dir1, s);
		updateSerpentPlateau(s,p,queue);
		showPlateau(p);
	}
	printf("\n vous avez perdu");
}
