#include "snake.h"
#include "element.h"
#include "plateau.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>

serpent snake;
serpent schlanga;
plateau p;
// Résultat : 0 : Pas de collision / 1 : Collision du schlanga - Victoire du snake / 2 : Collision du snake - Victoire du schlanga
int resultat;

plateau initJeu(int lon, int lar, int t) {
	int i;
// Le plateau est de taille longeur +2 et largeur+2 vu qu'il contient les murs
	p = initPlateau(lon+2, lar+2);
	initMurs(p);

	position pos_snake = cree_position(1,1);
	position pos_schlanga = cree_position(lon,lar);
	snake=init_serpent(t, pos_snake, BAS);
	schlanga=init_serpent(t, pos_schlanga, HAUT);

	addSerpentPlateau(snake, p);
	addSerpentPlateau(schlanga, p);
}


plateau updateJeu (direction dir1_snake) {
	position queue_snake = get_position_queue(snake);
	position queue_schlanga = get_position_queue(schlanga);  
	dir1_schlanga=aleatoire(schlanga,p);
	
	if (collision(p,dir1_schlanga,schlanga) == 1){ 	// Si on a une collision, on ne fait pas de déplacement et on doit sortir de la boucle while	
		resultat=1;
	}
	else if (collision(p,dir1_snake,snake) == 1){
		resultat=2;
	}
	else {				// Sinon, on doit effectuer le déplacement, mettre à jour le tableau et l'afficher
		schlanga = deplacement(dir1_schlanga, schlanga);
		snake = deplacement(dir1_snake, snake);
		updateSerpentPlateau(schlanga,p,queue_schlanga);
		updateSerpentPlateau(snake,p,queue_snake);
	}
	return p;
}

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
	while (b == 0){
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
		dir2 = aleatoire(schlanga, p);
		snake = deplacement(dir1, snake);
		schlanga = deplacement(dir2, schlanga);
		updateSerpentPlateau(snake,p,queue);
		updateSerpentPlateau(schlanga,p,queue1);
		showPlateau(p);
	}
	printf("\n vous avez perdu");
}
