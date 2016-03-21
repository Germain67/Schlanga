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
#define MOVE_TIME 200

direction dir = DROITE;
Uint32 lastMove = 0;
Uint32 lastRefresh = 0;
plateau p;

int main(int argc, char *argv[])
{
  printf("1)Jouer\n2)Test unitaires\n");
  char c;
  printf("Choix du menu : ");
  scanf(" %c",&c);
  printf("\n");

  int continuer = 1;
  SDL_Surface *ecran = NULL;
  SDL_Event event;
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(700, 700, 32, SDL_HWSURFACE);

  if( c == '2') {
    initEcran(ecran);
    while(1){
      printf("1) Test unitaire de la fonction displayPlateau et initMurs permettant l'affichage d'un plateau avec des murs \n");
      printf("2) Test unitaire de la fonction collision \n");
      printf("3) Test unitaire de la fonction addSerpentPlateau \n");
      printf("4) Test unitaire de la fonction updateSerpentPlateau \n");
      printf("5) Quitter \n");
      char d;
      printf("Choix du menu : ");
      scanf(" %c",&d);
      printf("\n");
      if ( d == '1') {
        test_displayPlateau_initMurs();
      }
      else if ( d == '2') {
        test_collision();
      }
      else if ( d == '3') {
        test_addSerpentPlateau();
      }
      else if ( d == '4') {
        test_updateSerpentPlateau();
      }
      else if (d == '5'){
        return 0;
      }
      else {
        printf("Vous n'avez pas sélectionné un menu qui existe. \n");
      }
    }
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
        int etatPartie = 0;
        p = updateJeu(p, dir, &etatPartie);
        if(etatPartie == 1){
          printf("Vous avez gagné !\n");
          break;
        }
        else if(etatPartie == 2){
          printf("Vous avez perdu !\n");
          break;
        }
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
