#include <stdio.h>
#include <stdlib.h>

/* Snake */
typedef struct position{
  int x;
  int y;
} *position;

typedef struct serpent {
  position coordonnees;
  struct maillon *suivant;
} *serpent;


typedef enum
{
  HAUT, BAS, GAUCHE, DROITE
} direction;

serpent cons(serpent s, position p);
serpent eliminer(serpent s);
void deplacement(direction d, serpent s);
