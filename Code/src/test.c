#include "plateau.h"
#include "snake.h"
#include "sdl_functions.h"
#include <time.h>
#include <SDL/SDL.h>

SDL_Surface* ecran = NULL;

void initEcran(SDL_Surface* ecr){
	ecran = ecr;
}

// Test de la fonction displayPlateau et initMurs permettant l'affichage d'un plateau avec des murs autour.
void test_displayPlateau_initMurs() {
	printf("Test de la fonction displayPlateau \n");
	printf("Initialisation d'un plateau de taille 10*10 \n");
	plateau p=initPlateau(10,10);
	initMurs(p);
	printf("Affichage du plateau \n");
	displayPlateau(ecran, p);
	free_plateau(p);
	free(ecran);
	sleep(2);
}

// Test une collision
void test_collision() {
	int choix;
	position pos, pos1, pos2;
	serpent s,s1,s2;
	plateau p;
	printf("Test de la fonction collision \n");
	printf("1. Collision avec un mur \n");
	printf("2. Collision avec un serpent \n");
	printf("3. Déplacement vers une case vide \n \n");
	printf("Choix du test à effectuer : ");
	scanf("%i",&choix);
	printf("\n");
	switch(choix) { 
	case 1: 
		p=initPlateau(10,10);
		initMurs(p);
		// On crée un serpent en haut à gauche d'un plateau et on teste si il observe une collision vers le HAUT 
		pos=cree_position(1, 1);
		s=init_serpent(5, pos, DROITE);
		addSerpentPlateau(s, p, 0);
		displayPlateau(ecran, p);

		if (collision(p,HAUT,s)==1) {
			printf("Collision nous indique une collision en allant vers le HAUT où il y a un mur, le test est réussi. \n");
		}
		else {
			printf("Collision ne nous indique pas une collision en allant vers le HAUT où il y a un mur, le test n'est pas réussi. \n");
		}
		free(p);
		free_position(pos);
		free_serpent(s);
		
	break;

	case 2: 
 		p=initPlateau(10,10);
		initMurs(p);
		// On crée deux serpents qui se touchent de façon à ce qu'il y ait une collision si le serpent s1 va vers le bas.
		pos1=cree_position(3, 2); 
		s1=init_serpent(5, pos1, BAS);
		addSerpentPlateau(s1, p, 0);

		pos2=cree_position(2, 7);
		s2=init_serpent(5, pos2, DROITE);
		addSerpentPlateau(s2, p, 1);

		displayPlateau(ecran, p);
		if (collision(p,BAS,s1)==1) {
			printf("Collision nous indique une collision vers le bas pour le serpent vertical, le test est réussi. \n");
		}
		else {
			printf("Collision ne nous indique pas une collision vers le bas pour le serpent vertical, le test n'est pas réussi. \n");
		}
		free(p);
		free_position(pos1);
		free_serpent(s1);
		free_position(pos2);
		free_serpent(s2);
		
	break;
	 
	case 3: 
		p=initPlateau(10,10);
		initMurs(p);
		// On crée un serpent de façon à qu'il puisse se déplacer vers le BAS où la case est vide.
		pos=cree_position(1, 1);
		s=init_serpent(5, pos, DROITE);
		addSerpentPlateau(s, p, 0);

		displayPlateau(ecran, p);
		if (collision(p,BAS,s)==0) {
			printf("Collision nous indique que l'on peut se déplacer vers la droite, le test est réussi. \n");
		}
		else {
			printf("Collision ne nous indique pas que l'on peut se déplacer vers la droite, le test n'est pas réussi. \n");
		}
		free(p);
		free_position(pos);
		free_serpent(s);

	break; 

	default: 
	printf("Vous n'avez pas sélectionné un menu qui existe. \n");
	}
	sleep(2);
}

// Test de la fonction addSerpentPlateau permettant l'ajout d'un serpent au plateau
void test_addSerpentPlateau(){
	printf("Test de la fonction addSerpentPlateau \n");
	plateau p=initPlateau(10,10);
	initMurs(p);
	
	displayPlateau(ecran, p);
	printf("Plateau avant l'ajout du serpent \n");

	sleep(1);

	position pos=cree_position(1, 1);
	serpent s=init_serpent(5, pos, DROITE);

	addSerpentPlateau(s, p, 0);
	displayPlateau(ecran, p);
	printf("Plateau après l'ajout du serpent \n");
	sleep(2);
	free(p);
	free_serpent(s);
}

// Test de la fonction updateSerpentPlateau permettant la mise à jour de la position d'un serpent sur le plateau (suppression de la queue de serpent antérieur et ajout de la tête du serpent suivant)
void test_updateSerpentPlateau(){
	printf("Test de la fonction updateSerpentPlateau \n");
	plateau p=initPlateau(10,10);
	initMurs(p);
	position pos=cree_position(1, 1);
	serpent s=init_serpent(5, pos, DROITE);

	addSerpentPlateau(s, p, 0);
	displayPlateau(ecran, p);
	printf("Plateau avant la mise à jour du serpent \n");

	sleep(1);
	
	position queue=get_position_queue(s);
	s=deplacement(DROITE,s);
	updateSerpentPlateau(s,p,queue,0);

	displayPlateau(ecran, p);
	printf("Plateau après la mise à jour du serpent \n");
	sleep(2);
	free(p);
	free_serpent(s);
	free_position(pos);
}

void free_ecran () {
	free(ecran);
}
