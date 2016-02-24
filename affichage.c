#include "snake.h"

plateau initPlateau(int hauteur, int largeur){
	plateau p = (plateau) malloc(hauteur * largeur * sizeof(element) + 2 * sizeof(int));
	p->data = (element**) malloc(hauteur * largeur * sizeof(element));
	p->hauteur = hauteur;
	p->largeur = largeur;
	return p;
}

element initElement(typeCase t){
	element e = (element) malloc(sizeof(element));
	e->type = t;
	return e;
}

char caseSymbol(element elem){
	char symbol;
	if(elem->type == mur){
		symbol = '*';
	}
	else if(elem->type == vide){
    symbol = ' ';
	}
	else if(elem->type == snake){
		symbol = '0';
	}
	return symbol;
}

void showPlateau(plateau p){
	//Clear console
	system("cls");
	//Affiche le plateau
	int x, y;
	for(x = 0; x<p->largeur; x++){
		char ligne[p->largeur];
		for(y = 0; y<p->hauteur; y++){
			element currentCase = p->data[x][y];
			char symbol = caseSymbol(currentCase);
			ligne[y] = symbol;
		}
		printf("%s\n", ligne);
	}
}

int main(){
	printf("initPlateau \n");
	plateau p = initPlateau(2, 2);
	printf("initElement \n");
	p->data[0][0] = initElement(vide);
	p->data[1][0] = initElement(snake);
	p->data[1][1] = initElement(mur);
	p->data[0][1] = initElement(snake);
	printf("showPlateau \n");
	showPlateau(p);
	getchar();
	return 0;
}