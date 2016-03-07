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
	while (collision(p,dir1,s) == 0){
	/*for (i=0;i<100;i++){*/
		scanf("%d", &dir);
		position queue = get_position_queue(s);
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
		updateSerpentPlateau(s,p,queue);
		showPlateau(p);
	}
	printf("\n vous avez perdu");
}
