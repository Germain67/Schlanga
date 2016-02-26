#include <stdio.h>
#include <stdlib.h>

/*Snake */
typedef struct serpent {
  position coordonnees;
  struct maillon *suivant;
} *serpent;

serpent cons(serpent s, position p);
serpent eliminer(serpent s);
serpent deplacement(int d, serpent s);