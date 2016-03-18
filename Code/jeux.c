#include "snake.h"
#include "element.h"
#include "plateau.h"
#include <stdio.h>
#include <stdlib.h>

/*
void jeux(){
	int i;
	plateau p = initPlateau(20, 20);
	initMurs(p);
	position pos = cree_position(10,5);
	serpent s = init_serpent(10, pos, HAUT);
	addSerpentPlateau(s, p);
	showPlateau(p);
	int dir = 0;
	direction dir1;
	int b = 0;
	while (b == 0){
		position queue = get_position_queue(s);
		
		dir = 0; // 
		while ((dir != 2) && (dir != 4) && (dir != 6) && (dir != 8)) { // On demande au joueur de choisir une touche 2,4,6,8 sinon, le jeu ne fait rien
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
		}

		if (collision(p,dir1,s) == 1){ 	// Si on a une collision, on ne fait pas de déplacement et on doit sortir de la boucle while
			b=1;
		}
		else {				// Sinon, on doit effectuer le déplacement, mettre à jour le tableau et l'afficher
			s = deplacement(dir1, s);
			updateSerpentPlateau(s,p,queue);
			showPlateau(p);
		}
	}
	printf("\n vous avez perdu\n");
}*/
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
		if (collision(p, dir1,s) == 1){
			b = 1;
		}
		else{
			s = deplacement(dir1, s);
			suppression_queue(s);
			updateSerpentPlateau(s,p,queue);
			showPlateau(p);
		}
		
	}
	printf("\n vous avez perdu");
}
