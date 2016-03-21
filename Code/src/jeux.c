#include "jeux.h"

serpent snake_joueur;
serpent schlanga;

// Résultat : 0 : Pas de collision / 1 : Collision du schlanga - Victoire du snake / 2 : Collision du snake - Victoire du schlanga
int resultat;

plateau initJeu(plateau p, int lon, int lar, int t) {
	// Le plateau est de taille longeur +2 et largeur+2 vu qu'il contient les murs
	p = initPlateau(lon+2, lar+2);
	initMurs(p);

	position pos_snake = cree_position(10,10);
	position pos_schlanga = cree_position(lon - 10,lar - 10);
	snake_joueur=init_serpent(t, pos_snake, DROITE);
	schlanga=init_serpent(t, pos_schlanga, GAUCHE);

	addSerpentPlateau(snake_joueur, p, 0);
	addSerpentPlateau(schlanga, p, 1);
	return p;
}


plateau updateJeu (plateau p, direction dir1_snake, int* etatPartie) {
	*etatPartie = 0;
	position queue = get_position_queue(snake_joueur);
	position queue1 = get_position_queue(schlanga);
	direction dir2 = aleatoire(schlanga, p);
	if (collision(p,dir2,schlanga) == 1){
		*etatPartie = 1;
	}
	schlanga = deplacement(dir2, schlanga);
	updateSerpentPlateau(schlanga,p,queue1);
	if (collision(p,dir1_snake,snake_joueur) == 1){
		*etatPartie = 2;
	}
	snake_joueur = deplacement(dir1_snake, snake_joueur);
	updateSerpentPlateau(snake_joueur,p,queue);
	return p;
}
