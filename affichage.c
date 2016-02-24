#include "snake.h"

plateau initPlateau(int hauteur, int largeur){
	plateau->data = malloc(hauteur*largeur*sizeof(element));
	plateau->hauteur = hauteur;
	plateau->largeur = largeur;
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
	plateau p =
	return 0;
}