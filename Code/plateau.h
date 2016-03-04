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

void addSerpentPlateau(serpent s, plateau p);
void updateSerpentPlateau(serpent tete, plateau p, position queue);
plateau initPlateau(int hauteur, int largeur);
void showPlateau(plateau p);

#endif