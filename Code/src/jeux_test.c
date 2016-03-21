#include "jeux_test.h"

serpent snake_joueur;
serpent schlanga;
plateau p;
// Résultat : 0 : Pas de collision / 1 : Collision du schlanga - Victoire du snake / 2 : Collision du snake - Victoire du schlanga
int resultat;


plateau initJeu(int lon, int lar, int t) {
	// Le plateau est de taille longeur +2 et largeur+2 vu qu'il contient les murs
	p = initPlateau(lon+2, lar+2);
	initMurs(p);

	position pos_snake = cree_position(1,1);
	position pos_schlanga = cree_position(lon,lar);
	snake_joueur=init_serpent(t, pos_snake, DROITE);
	schlanga=init_serpent(t, pos_schlanga, GAUCHE);

	addSerpentPlateau(snake_joueur, p);
	addSerpentPlateau(schlanga, p);
	return p;
}


plateau updateJeu (direction dir1_snake) {
	position queue = get_position_queue(snake_joueur);
	position queue1 = get_position_queue(schlanga);
	direction dir2 = aleatoire(schlanga, p);
	if (collision(p,dir2,schlanga) == 1){
		resultat = 1;
		//printf("schlanga");
	}
	schlanga = deplacement(dir2, schlanga);
	updateSerpentPlateau(schlanga,p,queue1);
	if (collision(p,dir1,snake) == 1){
		resultat = 2;
		//printf("snake");
	}
	snake_joueur = deplacement(dir1, snake_joueur);
	updateSerpentPlateau(snake_joueur,p,queue);
	return p;
}
