/**
 * \struct plateau.h
*/
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
void free_element(plateau p, int x, int y);
void free_plateau(plateau p);
void initMurs(plateau p);
void addSerpentPlateau(serpent s, plateau p, int isSchlanga);
void updateSerpentPlateau(serpent tete, plateau p, position queue, int isSchlanga, direction dir, typeCase Case);
int collision(plateau p, direction d, serpent s);
int collision_coord(plateau p, int x, int y);
typeCase collision_type(plateau p, direction d, serpent s);
int appartient_plateau(position p , plateau plat);
int deadend(plateau p, direction d, serpent s);


#endif
