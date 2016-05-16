//
// Created by lise on 07/03/16.
//

/**
 * \struct IA.h
*/


#ifndef SCHLANGA_IA_H
#define SCHLANGA_IA_H

#include "IA.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "element.h"
#include "plateau.h"

direction aleatoire(serpent schlanga, plateau p);
direction IA_defensif_direction(serpent schlanga, plateau p);
direction IA_agressif_direction(serpent schlanga, serpent snake, plateau p);

#endif //SCHLANGA_IA_H
