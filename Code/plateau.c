#include "plateau.h"
#include "snake.h"

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

void showPlateau(plateau p){
	//Clear console
	//system("clear");
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
		printf("mort par snake \n");
		b=1;
	}
	if (p->data[x][y]->type == mur ) {
		printf("mur \n");
		b=1;
	}
	if (p->data[x][y]->type == objet ) {
		printf("objet \n");
		b=1;
	}
	return b;
}

