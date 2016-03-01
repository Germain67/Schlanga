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

void ajout_entete(serpent s, position p);
void suppression_queue(serpent s);
void deplacement(direction d, serpent s);
