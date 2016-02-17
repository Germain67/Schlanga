//
// Created by lise on 17/02/16.
//

#include "snake.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int x;
    int y;
} coord;


typedef struct maillon {
    coord donnee;
    struct maillon *suivant;
} *snake;

typedef enum case {snake, item, vide, mur };

typedef case **plateau;