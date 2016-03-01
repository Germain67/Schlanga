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
plateau initPlateau(int hauteur, int largeur);
void showPlateau(plateau p);

#endif