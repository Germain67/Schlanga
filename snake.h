#include <stdio.h>
#include <stdlib.h>

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