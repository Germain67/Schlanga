/**
 * \struct snake.h
*/


#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>

/* Snake */
typedef struct position{
  int x;
  int y;
} *position;

typedef struct serpent {
  position coordonnees;
  struct serpent *suivant;
} *serpent;

/*
 * \enum direction
 * \brief énumération des directions possibles pour le déplacement via les touches directionnelles
 *
 */

typedef enum {
  HAUT, BAS, GAUCHE, DROITE
} direction;

serpent init_serpent(int taille, position pos_init, direction dir);
position cree_position(int x, int y);
void affiche_position(position p);
void affiche_serpent(serpent s);
void free_position(position pos);
serpent ajout_entete(serpent suivant, position pos);
position get_position_queue(serpent s);
void suppression_queue(serpent s);
serpent free_serpent(serpent s);
serpent deplacement(direction d, serpent s);
serpent init_serpent(int taille, position pos, direction dir);
int appartient(position x, serpent l);

#endif
