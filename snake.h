#include <stdio.h>
#include <stdlib.h>
#include "snake.c"

/* Position */

typedef struct {
    int x;
    int y;
} *position;

/*Snake */

typedef struct serpent {
  position coordonnees;
  struct serpent *suivant;
} *serpent;

/* Items */

typedef enum
{
  boost, invicibilite
} typeItem;

typedef struct item {
  typeItem t;
} item;

/* Cases et plateau */

typedef enum
{
  snake, objet, mur, vide 
} typeCase;

typedef struct element{
  typeCase type;
} *element;

typedef struct plateau{
	element** data;
	int hauteur;
	int largeur;
} *plateau;

/*ajout element a la tete du snake*/

serpent cons(serpent s, position p);

/*eliminer le dernier element du snake*/

serpent eliminer(serpent s);

/*deplacement*/

serpent deplacement(int d, serpent s);

