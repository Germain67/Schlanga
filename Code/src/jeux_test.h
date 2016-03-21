#ifndef JEUX_TEST_H
#define JEUX_TEST_H

#include "snake.h"
#include "element.h"
#include "plateau.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>

plateau initJeu(plateau p, int lon, int lar, int t);
plateau updateJeu (plateau p, direction dir1_snake);
void jeux();

#endif
