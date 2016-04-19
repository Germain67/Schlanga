#ifndef PLATEAU_H
#define PLATEAU_H

#include "element.h"
#include "snake.h"

/* Plateau */
typedef struct plateau{
	element** data;
	int hauteur;
	int largeur;
} *plateau;


/**
 * \fn       initPlateau
 * \brief    génère et alloue la mémoire d'un plateau de cases vides
 * \param    hauteur du plateau
 * \param    largeur du plateau
 * \return   plateau initialisé
 */

plateau initPlateau(int hauteur, int largeur);
void free_element(plateau p, int x, int y);
void free_plateau(plateau p);
void initMurs(plateau p);
void addSerpentPlateau(serpent s, plateau p, int isSchlanga);
void updateSerpentPlateau(serpent tete, plateau p, position queue, int isSchlanga);
int collision(plateau p, direction d, serpent s);

#endif
