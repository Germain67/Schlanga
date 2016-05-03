#ifndef JEUX_H
#define JEUX_H

#include "snake.h"
#include "element.h"
#include "plateau.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>

plateau initJeu(int lon, int lar, int t, int diff);
plateau updateJeu (plateau p, direction dir1_snake, int* etatPartie);
void fin_de_partie_serpent();

#endif
