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


typedef enum {
  HAUT, BAS, GAUCHE, DROITE
} direction;

serpent init_serpent(serpent suivant, position pos);
position cree_position(int x, int y);
serpent ajout_entete(serpent s, position p);
void suppression_queue(serpent s);
serpent free_serpent(serpent s);
void deplacement(direction d, serpent s);

#endif
