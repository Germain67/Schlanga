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

serpent init_serpent(int taille, position pos, direction dir);
position cree_position(int x, int y);
serpent ajout_entete(serpent suivant, position p);
position get_position_queue(serpent s);
void suppression_queue(serpent s);
serpent free_serpent(serpent s);
serpent deplacement(direction d, serpent s);
serpent init_serpent(int taille, position pos, direction dir);

#endif
