#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"
#include "plateau.h"
#include "snake.h"

void showRectangle(SDL_Surface* ecran, int x, int y, int size, int height, Uint32 R, Uint32 G, Uint32 B);
void displayPlateau(SDL_Surface* ecran, plateau p);

#endif