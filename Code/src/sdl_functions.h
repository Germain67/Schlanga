#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"
#include "plateau.h"
#include "snake.h"

void displayPicture(SDL_Surface* ecran, int x, int y, char* file);
void displayPlateau(SDL_Surface* ecran, plateau p);

#endif