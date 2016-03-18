#include "jeux_test.h"

serpent snake_joueur;
serpent schlanga;
plateau p;
// Résultat : 0 : Pas de collision / 1 : Collision du schlanga - Victoire du snake / 2 : Collision du snake - Victoire du schlanga
int resultat;

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


plateau initJeu(int lon, int lar, int t) {
	int i;
// Le plateau est de taille longeur +2 et largeur+2 vu qu'il contient les murs
	p = initPlateau(lon+2, lar+2);
	initMurs(p);

	position pos_snake = cree_position(1,1);
	position pos_schlanga = cree_position(lon,lar);
	snake_joueur=init_serpent(t, pos_snake, BAS);
	schlanga=init_serpent(t, pos_schlanga, HAUT);

	addSerpentPlateau(snake_joueur, p);
	addSerpentPlateau(schlanga, p);
}


plateau updateJeu (direction dir1_snake) {
	position queue_snake = get_position_queue(snake_joueur);
	position queue_schlanga = get_position_queue(schlanga);  
	direction dir1_schlanga=aleatoire(schlanga,p);
	
	if (collision(p,dir1_schlanga,schlanga) == 1){ 	// Si on a une collision, on ne fait pas de déplacement et on doit sortir de la boucle while	
		resultat=1;
	}
	else if (collision(p,dir1_snake,snake_joueur) == 1){
		resultat=2;
	}
	else {				// Sinon, on doit effectuer le déplacement, mettre à jour le tableau et l'afficher
		schlanga = deplacement(dir1_schlanga, schlanga);
		snake_joueur = deplacement(dir1_snake, snake_joueur);
		updateSerpentPlateau(schlanga,p,queue_schlanga);
		updateSerpentPlateau(snake_joueur,p,queue_snake);
	}
	return p;
}
