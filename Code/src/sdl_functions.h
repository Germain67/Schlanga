/**
 * \struct sdl_functions.h
*/

#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"
#include "plateau.h"
#include "snake.h"

void initOptions(int* tailleS, int* tailleP, int* vitesse, int* objets, int* diff);
void displayPicture(SDL_Surface* ecran, int x, int y, char* file);
void displayPlateau(SDL_Surface* ecran, plateau p);
void displayMenu(SDL_Surface* ecran, int position);
void displayOptions(SDL_Surface* ecran, int selected, int selectedColumn);
void Gameover(SDL_Surface *ecran, int compteur, char* mess);
void showLiveScore(SDL_Surface *ecran, int time, int score, int l);

#endif
