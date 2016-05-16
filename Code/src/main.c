/**
 * \file      main.c
 * \date      19 avril 2016
 * \brief     Main chargée de l'affichage du menu et du jeu
  ainsi que la capture des événements des touches
 *
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"
#include "plateau.h"
#include "snake.h"
#include "jeux.h"
#include "sdl_functions.h"
#define FPS 30
#define KEYDOWN_TIME 200
#define NB_MENU_ENTRY 4
#define NB_OPTIONS_ENTRY 6

int selected = 0;
int selectedColumn = 0;
Uint32 lastRefresh = 0;
Uint32 lastKeyPress = 0;
Uint32 lastMove = 0;
direction dir;
plateau p;
SDL_Surface *screen = NULL;
SDL_Event event;
int score = 0;

/* Options */

int tailleS = 10;
int tailleP = 20;
int vitesse = 1;
int objets = 0;
int diff = 1;

/*Scores*/

int highscores[100] = {};


/**
* \fn       showOptions
* \brief    Affiche les options du jeu (à implémenter)
*/

void showOptions(){
  int continuer = 1;
  
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);

  selected = 0;
  initOptions(&tailleS, &tailleP, &vitesse, &objets, &diff);

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
                case SDLK_RETURN:
                    if(selected == 5){
                      continuer = 0;
                    }
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
                case SDLK_RIGHT:
                    if (tempsActuel - lastKeyPress > KEYDOWN_TIME)
                    {
                      selectedColumn = 1;
                      lastKeyPress = tempsActuel;
                    }
                    break;
                case SDLK_LEFT:
                    if (tempsActuel - lastKeyPress > KEYDOWN_TIME)
                    {
                      selectedColumn = -1;
                      lastKeyPress = tempsActuel;
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
      displayOptions(screen, selected, selectedColumn);
      lastRefresh = tempsActuel;
      selectedColumn = 0;
    }
  }
}

// Fonction qui trie les 7 meilleurs scores dans un tableau highscores
void tri_scores(int score) {

    highscores[99]=score;

    int i, j;
    double elementInsere;

    for (i = 1; i < 100; i++) {
        /* Stockage de la valeur en i */
        elementInsere = highscores[i];
        /* Décale les éléments situés avant highscores[i] vers la droite
           jusqu'à trouver la position d'insertion */
        for (j = i; j > 0 && highscores[j - 1] < elementInsere; j--) {
            highscores[j] = highscores[j - 1];
        }
        /* Insertion de la valeur stockée à la place vacante */
        highscores[j] = elementInsere;
    }
}

//Fonction qui écrit les scores stockés dans le tableau Highscores dans un fichier .txt
void memScores() {
    FILE* fichier = NULL;
    fichier = fopen("fonts/scores.txt", "w");
    int i, compteur=1;

    if (fichier != NULL)
    {
        for (i=0; i<100; i++) {
            compteur=i+1;
            fprintf(fichier, "%d - %d\n", compteur, highscores[i]);
        }
        fclose(fichier);
    }
}

/**
* \fn       showScores
* \brief    Affiche les scores du jeu
*/

    void showScores() {
        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();
        putenv("SDL_VIDEO_CENTERED=1");
        SDL_Surface *ecran = NULL, *texte = NULL, *fond = NULL, *score=NULL;
        SDL_Rect position;
        SDL_Event event;
        TTF_Font *police = NULL;
        SDL_Color couleurNoire = {0, 0, 0};
        int continuer = 1, i=0;
        ecran = SDL_SetVideoMode(640, 680, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        //SDL_WM_SetCaption("Classement", NULL);
        fond = IMG_Load("images/sable.jpg");

        /* Chargement de la police */
        police = TTF_OpenFont("fonts/angelina.ttf", 65);



        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond, NULL, ecran, &position); /* Blit du fond */
        SDL_Flip(ecran);


        texte = TTF_RenderText_Blended(police, "Meilleurs scores:", couleurNoire);
        position.x = 180;
        position.y = 30;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);

        position.x += 50;
        FILE* fichier = NULL;
        char chaine[100]=""; // Chaîne vide de taille 100
        int nb=0;
        char nom[100];
        char lettrenom;
        fichier = fopen("fonts/scores.txt", "r");


        if (fichier != NULL)
        {
            for (i=0;i<7;i++)
            {
                lettrenom=fgetc(fichier);
                while (lettrenom != '\n')
                {
                    nom[nb]=lettrenom;
                    nb++;
                    lettrenom=fgetc(fichier);
                }
                nom[nb]='\0';
                sprintf(chaine, "%s",nom);
                position.y += 80;
                score = TTF_RenderText_Blended(police, chaine, couleurNoire);
                SDL_BlitSurface(score, NULL, ecran, &position);
                SDL_Flip(ecran);
                strcpy(nom,"");
                nb=0;


            }

            fclose(fichier);
        }

        while (continuer) {
            SDL_WaitEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;
                        default:
                            break;
                    }
            }

        }

        TTF_CloseFont(police);
        TTF_Quit();
        SDL_FreeSurface(texte);
        SDL_Quit();
    }


void fin_jeu(){
  int continuer = 1;
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  //SDL_WM_SetCaption("Fin du jeu !", NULL);
  Gameover(screen, score, "Vous avez perdu !");

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
                case SDLK_RETURN:
                    continuer = 0;
                    break;
                default:
                    break;
            }
            break;
        default:
          break;
    }
  }

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
  TTF_Init();
  screen = SDL_SetVideoMode(25*(l+2), 25*(h+2), 32, SDL_HWSURFACE);


  p = initJeu(l, h, tailleS, diff);
  dir = DROITE;

  int move_time = ((vitesse+3)%3) * -100 + 350;
  score = 0;
  Uint32 tempsActuel;
  Uint32 lastTime  = SDL_GetTicks();
  int temps = 0;

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
    tempsActuel = SDL_GetTicks();
    if (tempsActuel - lastMove > move_time) /* Si 30 ms se sont écoulées */
    {
      int etatPartie = 0;
      score += 1;
      p = updateJeu(p, dir, &etatPartie);
      if(etatPartie == 1){
        printf("Vous avez gagné !\n");
        break;;
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
      showLiveScore(screen, temps, score, l);
      lastRefresh = tempsActuel;
    }
    if(tempsActuel - lastTime > 1000){
      temps += 1;
      lastTime = tempsActuel;
    }
  }
    tri_scores(score);
    memScores();

   // Fin de partie, il faut tout free
  fin_de_partie_serpent();
  free_plateau(p);
  fin_jeu();

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
  int continuer = 1;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(400, 500, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Snake VS Schlangà", NULL);

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
                     startGame(tailleP,tailleP);
                      screen = SDL_SetVideoMode(400, 500, 32, SDL_HWSURFACE);
                      selected = 0;
                    }
                    else if(selected == 1){
                        memScores();
                      showScores();
                      screen = SDL_SetVideoMode(400, 500, 32, SDL_HWSURFACE);
                      selected = 1;
                    }
                    else if(selected == 2){
                      showOptions();
                      screen = SDL_SetVideoMode(400, 500, 32, SDL_HWSURFACE);
                      selected = 2;
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