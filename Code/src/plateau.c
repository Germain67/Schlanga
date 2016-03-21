#include "plateau.h"
#include "snake.h"
#include <time.h>

plateau initPlateau(int hauteur, int largeur){
	plateau p = (plateau) malloc(hauteur * largeur * sizeof(element) + 2 * sizeof(int));
	p->data = (element**) malloc(hauteur * sizeof(element*));
	int i;
	for(i = 0; i<hauteur ; i++){
		p->data[i] = (element*) malloc(largeur * sizeof(element));
		int j;
		for(j = 0; j<largeur; j++){
			p->data[i][j] = initElement(vide);
		}
	}
	p->hauteur = hauteur;
	p->largeur = largeur;
	return p;
}

void freePlateau(plateau p){
	element** tmp=p->data;
	int i;
	for (i=0; i < p->largeur; i++) {
		free(tmp[i]);
		tmp[i]=NULL;
	}
	free(tmp);
	tmp=NULL;
	p->largeur = 0;
	p->hauteur = 0;
}

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


void addSerpentPlateau(serpent s, plateau p){
	serpent temp = s;
	while(temp != NULL){
		p->data[temp->coordonnees->x][temp->coordonnees->y] = initElement(snake);
		temp = temp->suivant;
	}
}

void updateSerpentPlateau(serpent tete, plateau p, position queue){
	p->data[tete->coordonnees->x][tete->coordonnees->y] = initElement(snake);
	p->data[queue->x][queue->y] = initElement(vide);
}

void showPlateau(plateau p){
	//Clear console
	system("clear");
	//Affiche le plateau
	int x, y;
	for(x = 0; x<p->hauteur; x++){
		char ligne[p->largeur + 1];
		for(y = 0; y<p->largeur; y++){
			element currentCase = p->data[y][x];
			char symbol = caseSymbol(currentCase);
			ligne[y] = symbol;
		}
		ligne[p->largeur] = '\0';
		printf("%s\n", ligne);
	}
}

/* Collision */
/* b=1 : Collision -- b=0 : Pas de collision */
int collision(plateau p, direction d, serpent s){
	int x = s->coordonnees->x;
	int y = s->coordonnees->y;
	int b=0;	
	if (d==HAUT){
		y=y-1;
	}

	if (d==BAS){
		y=y+1;
	}
	
	if (d==DROITE){
		x=x+1;
    	}
    
	if (d==GAUCHE){
		x=x-1;
	}

	if (p->data[x][y]->type == snake ) {
		//printf("Rencontre un snake. \n");
		b=1;
	}
	if (p->data[x][y]->type == mur ) {
		//printf("Rencontre un mur \n");
		b=1;
	}
	if (p->data[x][y]->type == objet ) {
		//printf("Rencontre un objet \n");
		b=1;
	}
	return b;
}

// Test de la fonction showPlateau et initMurs permettant l'affichage d'un plateau avec des murs autour.
void test_showPlateau_initMurs() {
	printf("Test de la fonction showPlateau \n");
	printf("Initialisation d'un plateau de taille 10*10 \n");
	plateau p=initPlateau(10,10);
	initMurs(p);
	usleep(200);
	showPlateau(p);
	printf("Affichage du plateau \n");
	freePlateau(p);
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
		addSerpentPlateau(s, p);
		showPlateau(p);

		if (collision(p,HAUT,s)==1) {
			printf("Collision nous indique une collision en allant vers le HAUT où il y a un mur, le test est réussi. \n");
		}
		else {
			printf("Collision ne nous indique pas une collision en allant vers le HAUT où il y a un mur, le test n'est pas réussi. \n");
		}
		freePlateau(p);
		free_position(pos);
		free_serpent(s);
		
	break;

	case 2: 
 		p=initPlateau(10,10);
		initMurs(p);
		// On crée deux serpents qui se touchent de façon à ce qu'il y ait une collision si le serpent s1 va vers le bas.
		pos1=cree_position(3, 2); 
		s1=init_serpent(5, pos1, BAS);
		addSerpentPlateau(s1, p);

		pos2=cree_position(2, 7);
		s2=init_serpent(5, pos2, DROITE);
		addSerpentPlateau(s2, p);

		showPlateau(p);
		if (collision(p,BAS,s1)==1) {
			printf("Collision nous indique une collision vers le bas pour le serpent vertical, le test est réussi. \n");
		}
		else {
			printf("Collision ne nous indique pas une collision vers le bas pour le serpent vertical, le test n'est pas réussi. \n");
		}
		freePlateau(p);
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
		addSerpentPlateau(s, p);

		showPlateau(p);
		if (collision(p,BAS,s)==0) {
			printf("Collision nous indique que l'on peut se déplacer vers la droite, le test est réussi. \n");
		}
		else {
			printf("Collision ne nous indique pas que l'on peut se déplacer vers la droite, le test n'est pas réussi. \n");
		}
		freePlateau(p);
		free_position(pos);
		free_serpent(s);

	break; 

	default: 
	printf("Vous n'avez pas sélectionné un menu qui existe. \n"); 
	}
}

// Test de la fonction addSerpentPlateau permettant l'ajout d'un serpent au plateau
void test_addSerpentPlateau(){
	printf("Test de la fonction addSerpentPlateau \n");
	plateau p=initPlateau(10,10);
	initMurs(p);
	
	showPlateau(p);
	printf("Plateau avant l'ajout du serpent \n");

	sleep(1);

	position pos=cree_position(1, 1);
	serpent s=init_serpent(5, pos, DROITE);

	addSerpentPlateau(s, p);
	showPlateau(p);
	printf("Plateau après l'ajout du serpent \n");
}

// Test de la fonction updateSerpentPlateau permettant la mise à jour de la position d'un serpent sur le plateau (suppression de la queue de serpent antérieur et ajout de la tête du serpent suivant)
void test_updateSerpentPlateau(){
	printf("Test de la fonction updateSerpentPlateau \n");
	plateau p=initPlateau(10,10);
	initMurs(p);
	position pos=cree_position(1, 1);
	serpent s=init_serpent(5, pos, DROITE);

	addSerpentPlateau(s, p);
	showPlateau(p);
	printf("Plateau avant la mise à jour du serpent \n");

	sleep(1);
	
	position queue=get_position_queue(s);
	s=deplacement(DROITE,s);
	updateSerpentPlateau(s,p,queue);

	showPlateau(p);
	printf("Plateau après la mise à jour du serpent \n");
}

