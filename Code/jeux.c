#include "snake.h"
#include "element.h"
#include "plateau.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>

void jeux(){
	int i;
	plateau p = initPlateau(20, 20);
	initMurs(p);
	position pos = cree_position(10,10);
	position pos1 = cree_position(5,5);
	serpent snake = init_serpent(5, pos, BAS);
	serpent schlanga = init_serpent(5, pos1, HAUT);
	addSerpentPlateau(snake, p);
	addSerpentPlateau(schlanga, p);
	showPlateau(p);
	int dir = 8;
	direction dir1 = BAS;
	direction dir2 = HAUT;
	int b = 0;
	int a = 0;
	while (b == 0 && a == 0){
		position queue = get_position_queue(snake);
		position queue1 = get_position_queue(schlanga);
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
		if (collision(p,dir1,snake) == 1){
			b = 1;
		}
		if (collision(p,dir1,schlanga) == 1){
			a = 1;
		}
		dir2 = aleatoire(schlanga, p);
		snake = deplacement(dir1, snake);
		schlanga = deplacement(dir2, schlanga);
		updateSerpentPlateau(snake,p,queue);
		updateSerpentPlateau(schlanga,p,queue1);
		showPlateau(p);
	}
	if (a = 1){
		printf("\n vous avez gagné");
	}
	if (b = 1){
		printf("\n vous avez perdu");
	}

}
