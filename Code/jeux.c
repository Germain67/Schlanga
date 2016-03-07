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
	While (collision(plateau,dir,s) == 0){
		scanf("%i", &dir);
		if (dir == 2){
			s = deplacement(BAS, s);
		}
		if (dir == 8){
			s = deplacement(HAUT, s);
		}
		if (dir == 6){
			s = deplacement(DROITE, s);
		}
		if (dir == 4){
			s = deplacement(GAUCHE, s);
		}
		addSerpentPlateau(s, p);
		sshowPlateau(p);
	}
	printf("\n vous avez perdu", );
}
