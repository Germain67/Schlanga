#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"
#include "plateau.h"
#include "snake.h"
#include "jeux_test.h"
#define FPS 30

direction dir = BAS;
Uint32 elapsedTime;

void showRectangle(SDL_Surface* ecran, int x, int y, int size, int height){
  SDL_Surface *rectangle = NULL;
  SDL_Rect position;
  // Allocation de la surface
  rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, size, height, 32, 0, 0, 0, 0);
  position.x = x;
  position.y = y;
  SDL_BlitSurface(rectangle, NULL, ecran, &position); // Collage de la surface sur l'écran
}

void displayPlateau(SDL_Surface* ecran, plateau p){
  // Effacement de l'écran
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  //Affiche le plateau
  int x, y;
  for(x = 0; x<p->hauteur; x++){
    for(y = 0; y<p->largeur; y++){
      element currentCase = p->data[y][x];
      //char symbol = caseSymbol(currentCase);
      if(currentCase->type != vide){
        showRectangle(ecran,x*20,y*20,15,15);
      }
    }
  }
}

int main(int argc, char *argv[])
{
  int continuer = 1;
  SDL_Surface *ecran = NULL;
  SDL_Event event;
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(700, 700, 32, SDL_HWSURFACE);
  plateau p = initJeu(20, 20, 5);

  while (continuer)
  {
    elapsedTime = SDL_GetTicks();
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_UP:
                    dir = HAUT;
                    break;
                case SDLK_DOWN:
                    dir = BAS;
                    break;
                case SDLK_RIGHT:
                    dir = DROITE;
                    break;
                case SDLK_LEFT:
                    dir = GAUCHE;
                    break;
            }
            break;
    }
    //1 seconde
    if (elapsedTime%1000 == 0) /* Si 30 ms se sont écoulées */
    {
      plateau p = updateJeu(dir);

    }
    //30 FPS
    if (elapsedTime%(1000/FPS) == 0) /* Si 30 ms se sont écoulées */
    {
      printf("Dir : %d\n", dir);
      displayPlateau(ecran, p);
      //On met à jour sans clignotement
      SDL_Flip(ecran);
    }
  }

  return 0;
}
