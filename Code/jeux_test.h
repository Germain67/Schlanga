#ifndef JEUX_H
#define JEUX_H

#include <stdio.h>
#include <stdlib.h>

plateau initJeu(int lon, int lar, int t);
plateau updateJeu (direction dir1_snake);
void jeux();

#endif
