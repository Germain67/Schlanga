#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

/* Position */

typedef struct {
    int x;
    int y;
} position;

/*Snake */

typedef struct snake {
  position coordonnees;
  struct snake *suivant;
} *snake;

/* Items */

typedef struct item {
  typeItem t;
} *item;

enum typeItem
{
  boost, invicibilite
};

/* Cases et plateau */

typedef struct case{
  typeCase type;
}

enum typeCase
{
  snake, item, mur, vide 
};

typedef case **plateau;