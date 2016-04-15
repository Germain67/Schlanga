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

plateau initPlateau(int hauteur, int largeur);
void initMurs(plateau p);
void addSerpentPlateau(serpent s, plateau p, int isSchlanga);
void updateSerpentPlateau(serpent tete, plateau p, position queue, int isSchlanga);
int collision(plateau p, direction d, serpent s);


#endif
