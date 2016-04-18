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
#define MOVE_TIME 150

int selected = 0;
Uint32 lastRefresh = 0;
Uint32 lastKeyPress = 0;
Uint32 lastMove = 0;
direction dir = DROITE;
plateau p;
SDL_Surface *screen = NULL;
SDL_Event event;

void startGame(int l, int h){
  int continuer = 1;
  
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(27*l, 27*h, 32, SDL_HWSURFACE);

  p = initJeu(l, h, 10);

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
                    if(dir != BAS){
                      dir = HAUT;
                    }
                    break;
                case SDLK_DOWN:
                    if(dir != HAUT){
                      dir = BAS;
                    }
                    break;
                case SDLK_RIGHT:
                    if(dir != GAUCHE){
                      dir = DROITE;
                    }
                    break;
                case SDLK_LEFT:
                    if(dir != DROITE){
                      dir = GAUCHE;
                    }
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
      displayPlateau(screen, p);
      lastRefresh = tempsActuel;
    }
  }

   // Fin de partie, il faut tout free
  fin_de_partie_serpent();
  free_plateau(p);
}

int main(int argc, char *argv[])
{
  int l=25; int h=25; // Taille du plateau
  int continuer = 1;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(750, 750, 32, SDL_HWSURFACE);

  while (continuer)
  {
    SDL_PollEvent(&event);
    Uint32 tempsActuel = SDL_GetTicks();
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
                    if (tempsActuel - lastKeyPress > 200)
                    {
                      selected = (selected + 4)%5;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_DOWN:
                    if (tempsActuel - lastKeyPress > 200)
                    {
                      selected = (selected + 1)%5;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_RETURN:
                    if(selected == 0){
                      startGame(l,h);
                      continuer = 0;
                    }
                    else if(selected == 4){
                      continuer = 0;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
          break;
    }
    if (tempsActuel - lastRefresh > (1000/FPS)) /* Si 30 ms se sont écoulées */
    {
      displayMenu(screen, selected);
      lastRefresh = tempsActuel;
    }
  }

  // Fin de partie, il faut tout free
  SDL_FreeSurface(screen);
  SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
  SDL_Quit();

  return 0;
}

/*
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
  ecran = SDL_SetVideoMode(750, 750, 32, SDL_HWSURFACE);

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
*/
