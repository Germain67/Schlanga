#include "plateau.h"
#include "snake.h"

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


// À modifier
void free_plateau(plateau p) {
	int l = p->largeur;
	int h = p->hauteur;
	int i,j;
	for ( i = 0 ; i<l ; i++)
	{
		for ( j = 0 ; j<h ; j++) { 
      			free(p->data[i][j]);
		}
      		free(p->data[i]);
	}
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

// isSchlanga = 1 si c'est un Schlanga / 0 sinon
void addSerpentPlateau(serpent s, plateau p, int isSchlanga){
	serpent temp = s;
	while(temp != NULL){
		if (isSchlanga == 1) {
			p->data[temp->coordonnees->x][temp->coordonnees->y] = initElement(snake_schlanga);
		}
		else {
			p->data[temp->coordonnees->x][temp->coordonnees->y] = initElement(snake);
		}
		temp = temp->suivant;
	}
	free_serpent(temp);
}

void updateSerpentPlateau(serpent tete, plateau p, position queue, int isSchlanga){
	if(isSchlanga == 1){
		p->data[tete->coordonnees->x][tete->coordonnees->y] = initElement(snake_schlanga);
	}
	else{
		p->data[tete->coordonnees->x][tete->coordonnees->y] = initElement(snake);
	}
	p->data[queue->x][queue->y] = initElement(vide);
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
		b=1;
	}
	if (p->data[x][y]->type == snake_schlanga ) {
		b=1;
	}
	if (p->data[x][y]->type == mur ) {
		b=1;
	}
	if (p->data[x][y]->type == objet ) {
		b=1;
	}
	return b;
}
