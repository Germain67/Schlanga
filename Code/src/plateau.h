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
void freePlateau(plateau p);
void initMurs(plateau p);
void addSerpentPlateau(serpent s, plateau p, int isSchlanga);
void updateSerpentPlateau(serpent tete, plateau p, position queue);
void showPlateau(plateau p);
int collision(plateau p, direction d, serpent s);

// Fonctions de test
void test_showPlateau_initMurs();
void test_collision();
void test_addSerpentPlateau();
void test_updateSerpentPlateau();
#endif
