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

<<<<<<< 90a98ed19158c21cce1d1759a916603c0f6ba6e7
void ajout_entete(serpent s, position p);
void suppression_queue(serpent s);
=======
position cree_position(int x, int y);

serpent ajout_entete(serpent s, position p);

void suppression_queue(serpent s);

serpent Free_serpent(serpent s);

>>>>>>> 02043f1a4c54db3662742121357b9e8f14f811d0
void deplacement(direction d, serpent s);

#endif
