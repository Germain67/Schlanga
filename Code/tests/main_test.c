/**
 * \file      main_test.c
 * \date      19 avril 2016
 * \brief     Test des fuites de mémoire sous Valgrind.
 */

#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/plateau.h"
#include "../src/jeux.h"

int main() {
  plateau p;
  int lon=25, lar=25, t=10; // Test avec un plateau de taille 25*25 et des serpents de taille 10

  p=initJeu(lon, lar, t, 1); // Initialisation d'un plateau 25*25 avec des serpents de taille 10

  int etatPartie = 0; 
  p=updateJeu (p, HAUT, &etatPartie, 300, 0); // Mise à jour d'un plateau vers le jeu
  fin_de_partie_serpent();
  free_plateau(p);
  printf("JM je te suce la bite.\n");

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

