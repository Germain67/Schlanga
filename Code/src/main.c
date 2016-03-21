#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"
#include "plateau.h"
#include "snake.h"
#include "jeux.h"
#include "test.h"
#include "sdl_functions.h"
#define FPS 30
#define MOVE_TIME 500

direction dir = DROITE;
Uint32 lastMove = 0;
Uint32 lastRefresh = 0;
plateau p;

int main(int argc, char *argv[])
{
  printf("1)Jouer\n2)Test unitaires\n");
  char c;
  scanf(" %c",&c);

  int continuer = 1;
  SDL_Surface *ecran = NULL;
  SDL_Event event;
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(700, 700, 32, SDL_HWSURFACE);

  if( c == '2') {
    initEcran(ecran);
    test_showPlateau_initMurs();
    test_collision();
    test_addSerpentPlateau();
    test_updateSerpentPlateau();
  }
  else
  {
    plateau p = NULL;
    p = initJeu(p, 30, 30, 3);

    while (continuer)
    {
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
                  default:
                      break;
              }
              break;
          default:
            break;
      }

      Uint32 tempsActuel = SDL_GetTicks();
      if (tempsActuel - lastMove > MOVE_TIME) /* Si 30 ms se sont écoulées */
      {
        p = updateJeu(p, dir);
        lastMove = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
      }
      if (tempsActuel - lastRefresh > (1000/FPS)) /* Si 30 ms se sont écoulées */
      {
        displayPlateau(ecran, p);
        lastRefresh = tempsActuel;
      }
    }
  }

  return 0;
}
