#include "plateau.h"

void addSerpentPlateau(serpent s, plateau p){
	serpent temp = s;
	while(temp != NULL){
		p->data[s->coordonnees->x][s->coordonnees->y] = initElement(snake);
		temp = temp->suivant;
	}
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
	system("clear");
	//Affiche le plateau
	int x, y;
	for(x = 0; x<p->hauteur; x++){
		char ligne[p->largeur + 1];
		for(y = 0; y<p->largeur; y++){
			element currentCase = p->data[x][y];
			char symbol = caseSymbol(currentCase);
			ligne[y] = symbol;
		}
		ligne[p->largeur] = '\0';
		printf("%s\n", ligne);
	}
}