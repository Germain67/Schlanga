/**
 * \file      main.c
 * \date      19 avril 2016
 * \brief     Main chargée de l'affichage du menu et du jeu
  ainsi que la capture des événements des touches
 *
 */

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

/**
* \fn       showOptions
* \brief    Affiche les options du jeu (à implémenter)
*/

void showOptions(){
  //Non disponible pour le moment
}

/**
* \fn       showScores
* \brief    Affiche les scores du jeu (à implémenter)
*/

void showScores(){
  //TODO: Implémenter l'affichage des scores
}

/**
* \fn       startGame
* \brief    Démarre la partie, fait l'affichage du plateau à l'écran
             et la gestion des touches pour la direction du serpent
* \param    l : Largeur du plateau
* \param    h : Hauteur du plateau
*/

void startGame(int l, int h){
  int continuer = 1;
  
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(25*(l+2), 25*(h+2), 32, SDL_HWSURFACE);

  p = initJeu(l, h, 8);

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

/**
* \fn       main
* \brief    Fonction main du programme chargé de l'appel aux fonctions d'affichage du menu
             et de la gestion des touches dans le menu
* \return   Renvoie 0 si le programme s'est executé correctement
*/

int main()
{
  putenv("SDL_VIDEO_CENTERED=1"); 
  int l=20; int h=20; // Taille du plateau
  int continuer = 1;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(400, 500, 32, SDL_HWSURFACE);

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
                      selected = (selected + 3)%4;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_DOWN:
                    if (tempsActuel - lastKeyPress > 200)
                    {
                      selected = (selected + 1)%4;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_RETURN:
                    if(selected == 0){
                      startGame(l,h);
                      continuer = 0;
                    }
                    else if(selected == 1){
                      showScores();
                    }
                    else if(selected == 2){
                      showOptions();
                    }
                    else if(selected == 3){
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
    if (tempsActuel - lastRefresh > (1000/FPS)) // Si 30 ms se sont écoulées 
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
