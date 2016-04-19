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
#include "sdl_functions.h"
#define FPS 30
#define MOVE_TIME 150
#define KEYDOWN_TIME 200
#define NB_MENU_ENTRY 4
#define NB_OPTIONS_ENTRY 4

int selected = 0;
Uint32 lastRefresh = 0;
Uint32 lastKeyPress = 0;
Uint32 lastMove = 0;
direction dir;
plateau p;
SDL_Surface *screen = NULL;
SDL_Event event;

/**
* \fn       showOptions
* \brief    Affiche les options du jeu (à implémenter)
*/

void showOptions(){
  int continuer = 1;
  
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);

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
                    if (tempsActuel - lastKeyPress > KEYDOWN_TIME)
                    {
                      selected = (selected + NB_OPTIONS_ENTRY - 1)%NB_OPTIONS_ENTRY;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_DOWN:
                    if (tempsActuel - lastKeyPress > KEYDOWN_TIME)
                    {
                      selected = (selected + 1)%NB_OPTIONS_ENTRY;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_RETURN:
                    if(selected == 0){
                      
                    }
                    else if(selected == 1){
                      
                    }
                    else if(selected == 2){
                      
                    }
                    else if(selected == 3){
                      
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
      displayOptions(screen, selected, GAUCHE);
      lastRefresh = tempsActuel;
    }
  }
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
  dir = DROITE;

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
  int l=20; 
  int h=20; // Taille du plateau
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
                    if (tempsActuel - lastKeyPress > KEYDOWN_TIME)
                    {
                      selected = (selected + NB_MENU_ENTRY - 1)%NB_MENU_ENTRY;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_DOWN:
                    if (tempsActuel - lastKeyPress > KEYDOWN_TIME)
                    {
                      selected = (selected + 1)%NB_MENU_ENTRY;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_RETURN:
                    if(selected == 0){
                      startGame(l,h);
                      screen = SDL_SetVideoMode(400, 500, 32, SDL_HWSURFACE);
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