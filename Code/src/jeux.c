/**
 * \file     jeux.c
 * \date     19 avril 2016
 * \brief    contient les fonctions qui interviennent pendant la session de jeu
 */
#include "jeux.h"

serpent snake_joueur;
serpent schlanga;
int difficulte;
int vitesse;
int nb_item_lost;


/**
 * \fn       initjeu
 * \brief    initialise le plateau au démarrage du jeu
 * \details  cette fonction n'est appelée qu'au début d'une session de jeu
 * \param    lon  longueur du plateau à générer
 * \param    lar  largeur du plateau à générer
 * \param    t entier
 * \return   plateau initialisé avec un schlanga et un serpent
 */


plateau initJeu(int lon, int lar, int t, int diff) {
	difficulte = diff;
	// Le plateau est de taille longeur +2 et largeur+2 vu qu'il contient les murs
	plateau p = initPlateau(lon+2, lar+2);
	initMurs(p);

	position pos_snake = cree_position(2,2);
	position pos_schlanga = cree_position(lon - 2,lar - 2);
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

plateau updateJeu (plateau p, direction dir1_snake, int* etatPartie, int v, int nb) {
	vitesse=v;
	nb_item_lost=nb;
	*etatPartie = 0;
	position queue;
	position queue1;
	direction dir2;
	if(difficulte == 0){
		dir2 = aleatoire(schlanga, p);
	}
	else if(difficulte == 1)
	{
		dir2 = IA_defensif_direction(schlanga, p);
	}
	else
	{
		dir2 = IA_agressif_direction(schlanga, snake_joueur, p);
	}
	if (collision(p,dir2,schlanga) == 1){
		*etatPartie = 1;
	}
// Déplacement du schlanga
	typeCase Case_schlanga=collision_type(p,dir2,schlanga);	
	if (Case_schlanga == vide || Case_schlanga == mur || Case_schlanga == snake_schlanga || Case_schlanga == snake) {
		schlanga = deplacement(dir2, schlanga);
		queue1 = get_position_queue(schlanga);
		updateSerpentPlateau(schlanga,p,queue1, 1,dir2,Case_schlanga);
	}

	else if (Case_schlanga == grandir) {
		schlanga = deplacement_grandir(dir2, schlanga);
		queue1 = get_position_queue(schlanga);
		updateSerpentPlateau(schlanga,p,queue1, 1,dir2,Case_schlanga);
		nb_item_lost --;
	}

	else if (Case_schlanga == reduire) {
		schlanga = deplacement_reduire(dir2, schlanga);
		queue1 = get_position_queue(schlanga);
		updateSerpentPlateau(schlanga,p,queue1, 1,dir2,Case_schlanga);
    		suppression_queue(schlanga);
		queue1 = get_position_queue(schlanga);
		updateSerpentPlateau(schlanga,p,queue1, 1,dir2,Case_schlanga);
		nb_item_lost --;
	}
	else if (Case_schlanga == accelerer) {
		if (vitesse > 50) {
			vitesse=vitesse-50;
		}
		schlanga = deplacement(dir2, schlanga);
		queue1 = get_position_queue(schlanga);
		updateSerpentPlateau(schlanga,p,queue1, 1,dir2,Case_schlanga);
		nb_item_lost --;
	}
	else if (Case_schlanga == ralentir) {
		vitesse=vitesse+50;
		schlanga = deplacement(dir2, schlanga);
		queue1 = get_position_queue(schlanga);
		updateSerpentPlateau(schlanga,p,queue1, 1,dir2,Case_schlanga);
		nb_item_lost --;
	}

// Collision du snake
	if (collision(p,dir1_snake,snake_joueur) == 1){
		*etatPartie = 2;
	}
	
// Déplacement du snake
	typeCase Case_snake=collision_type(p,dir1_snake,snake_joueur);
	if (Case_snake == vide || Case_snake == mur || Case_snake == snake_schlanga || Case_snake == snake) {
		snake_joueur = deplacement(dir1_snake, snake_joueur);
		queue = get_position_queue(snake_joueur);
		updateSerpentPlateau(snake_joueur,p,queue, 0,dir1_snake,Case_snake);

	}

	else if (Case_snake == grandir) {
		snake_joueur = deplacement_grandir(dir1_snake, snake_joueur);
		queue = get_position_queue(snake_joueur);
		updateSerpentPlateau(snake_joueur,p,queue, 0,dir1_snake,Case_snake);
		nb_item_lost --;
	}

	else if (Case_snake == reduire) {
		snake_joueur = deplacement_reduire(dir1_snake, snake_joueur);
		queue = get_position_queue(snake_joueur);
		updateSerpentPlateau(snake_joueur,p,queue, 0,dir1_snake,Case_snake);
    		suppression_queue(snake_joueur);
		queue = get_position_queue(snake_joueur);
		updateSerpentPlateau(snake_joueur,p,queue, 0,dir1_snake,Case_snake);
		nb_item_lost --;
	}
	else if (Case_snake == accelerer) {
		if (vitesse > 50) {
			vitesse=vitesse-50;
		}
		snake_joueur = deplacement(dir1_snake, snake_joueur);
		queue = get_position_queue(snake_joueur);
		updateSerpentPlateau(snake_joueur,p,queue, 0,dir1_snake,Case_snake);
		nb_item_lost --;
	}
	else if (Case_snake == ralentir) {
		vitesse=vitesse+50;
		snake_joueur = deplacement(dir1_snake, snake_joueur);
		queue = get_position_queue(snake_joueur);
		updateSerpentPlateau(snake_joueur,p,queue, 0,dir1_snake,Case_snake);
		nb_item_lost --;
	}
	return p;
}

/**
 * \fn       updateVitesse
 * \brief    permet de mettre à jour la vitesse
 * \return   vitesse mise à jour
 */
int updateVitesse () {
	return vitesse;
}

/**
 * \fn       updateNbItem
 * \brief    permet de mettre à jour le nombre d'item quand un item est mangé
 * \return   vitesse mise à jour
 */
int updateNbItem_lost () {
	return nb_item_lost;
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
