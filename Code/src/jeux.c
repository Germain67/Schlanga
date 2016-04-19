/**
 * \file     jeux.c
 * \date     19 avril 2016
 * \brief    contient les fonctions qui interviennent pendant la session de jeu
 */
#include "jeux.h"

serpent snake_joueur;
serpent schlanga;


/**
 * \fn       initjeu
 * \brief    initialise le plateau au démarrage du jeu
 * \details  cette fonction n'est appelée qu'au début d'une session de jeu
 * \param    lon  longueur du plateau à générer
 * \param    lar  largeur du plateau à générer
 * \param    t entier
 * \return   plateau initialisé avec un schlanga et un serpent
 */


plateau initJeu(int lon, int lar, int t) {
	// Le plateau est de taille longeur +2 et largeur+2 vu qu'il contient les murs
	plateau p = initPlateau(lon+2, lar+2);
	initMurs(p);

	position pos_snake = cree_position(10,10);
	position pos_schlanga = cree_position(lon - 10,lar - 10);
	snake_joueur=init_serpent(t, pos_snake, DROITE);
	schlanga=init_serpent(t, pos_schlanga, GAUCHE);

	addSerpentPlateau(snake_joueur, p, 0);
	addSerpentPlateau(schlanga, p, 1);

	return p;
}

/**
 * \fn       updateJeu
 * \brief    permet de mettre à jour le plateau après chaque déplacement du schlanga ou du snake
 * \param    p  plateau à mettre à jour
 * \param    dir1_snake  direction dans laquelle doit aller le serpent ou le schlanga
 * \param    etatPartie  variable décrivant l'état de la partie: 0 pour une partie normale, 1 si le joueur a perdu, 2 si le schlanga a perdu
 * \return   plateau mis à jour
 */

plateau updateJeu (plateau p, direction dir1_snake, int* etatPartie) {
	*etatPartie = 0;
	position queue = get_position_queue(snake_joueur);
	position queue1 = get_position_queue(schlanga);
	direction dir2 = IA_defensif_direction(schlanga, p);
	if (collision(p,dir2,schlanga) == 1){
		*etatPartie = 1;
	}
	schlanga = deplacement(dir2, schlanga);
	updateSerpentPlateau(schlanga,p,queue1, 1);
	if (collision(p,dir1_snake,snake_joueur) == 1){
		*etatPartie = 2;
	}
	snake_joueur = deplacement(dir1_snake, snake_joueur);
	updateSerpentPlateau(snake_joueur,p,queue, 0);

	free_position(queue);
	free_position(queue1);

	return p;
}

/**
 * \fn       fin_de_partie_serpent
 * \brief    libère la mémoire allouée au serpent et au schlanga
 * \return   rien
 */


void fin_de_partie_serpent() {
	free_serpent(snake_joueur);
	free_serpent(schlanga);
}
