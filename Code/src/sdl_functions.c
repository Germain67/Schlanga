/**
 * \file      sdl_functions.c
 * \date      19 avril 2016
 * \brief     Fonctions utilisant la librairie SDL 
              servant à afficher le menu, le plateau de jeu et les images
 *
 */
#include "sdl_functions.h"

/**
* \fn       displayPicture
* \brief    Fonction chargée de l'affichage d'une image a la position x,y de la fenetre
* \param    *ecran : Pointeur vers l'écran
* \param    x : Position de l'image en x
* \param    y : Position de l'image en y
* \param    *file : Pointeur vers le fichier contenant l'image
*/

void displayPicture(SDL_Surface* ecran, int x, int y, char* file){
  SDL_Rect position;
  position.x = x;
  position.y = y;
  SDL_Surface *image = NULL;
  /* On charge l'image : */
  image = SDL_LoadBMP(file);
  /* Transparence */
  SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0, 0, 0));
  /* On colle l'image maintenant transparente sur le fond : */
  SDL_BlitSurface(image, NULL, ecran, &position);
  SDL_FreeSurface(image);
}

void printNumber(int number, SDL_Surface* ecran, int x, int y){
  int dizaine = number/10;
  char dizPicture[13];
  sprintf(dizPicture, "images/%d.bmp", dizaine);
  int unite = number%10;
  char unitPicture[13];
  sprintf(unitPicture, "images/%d.bmp", unite);
  displayPicture(ecran, x, y, dizPicture);
  displayPicture(ecran, x + 30, y, unitPicture);
}

/**
* \fn       displayPlateau
* \brief    Fonction chargée de l'affichage du plateau de jeu à l'écran
* \param    *ecran : Pointeur vers l'écran
* \param    p : Plateau à afficher
*/

void displayPlateau(SDL_Surface* ecran, plateau p){
  // Effacement de l'écran
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  //Affiche le plateau
  int x, y;
  for(x = 0; x<p->hauteur; x++){
    for(y = 0; y<p->largeur; y++){
      element currentCase = p->data[x][y];
      //Vert pour le snake
      if(currentCase->type == snake){
        displayPicture(ecran, x*25, y*25, "images/snake.bmp");
      }
      //Noir pour un mur
      else if(currentCase->type == mur){
        displayPicture(ecran, x*25, y*25, "images/mur.bmp");
      }
      //Rouge pour le schlanga
      else if(currentCase->type == snake_schlanga){
        displayPicture(ecran, x*25, y*25, "images/schlanga.bmp");
      }
    }
  }
  SDL_Flip(ecran);
}

/**
* \fn       displayMenu
* \brief    Fonction chargée de l'affichage du menu 
            ainsi que de l'affichage d'une fleche au niveau du choix courant
* \param    *ecran : Pointeur vers l'écran
* \param    selected : Index du choix dans le menu
*/

void displayMenu(SDL_Surface* ecran, int selected){
  // Effacement de l'écran
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  //Elements du menu
  displayPicture(ecran, 100, 50, "images/jouer.bmp");
  displayPicture(ecran, 100, 150, "images/scores.bmp");
  displayPicture(ecran, 100, 250, "images/options.bmp");
  displayPicture(ecran, 100, 350, "images/quitter.bmp");
  //Flèche
  displayPicture(ecran, 50, (selected + 1) * 100 - 65, "images/fleche.bmp");
  //Affichage
  SDL_Flip(ecran);
}

void displayOptions(SDL_Surface* ecran, int selected, direction dir){
  // Effacement de l'écran
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  //Elements des options
  //Serpent
  displayPicture(ecran, 100, 50, "images/serpents.bmp");
  printNumber(10, ecran, 300, 50);
  //Plateau
  displayPicture(ecran, 100, 150, "images/plateau.bmp");
  printNumber(20, ecran, 300, 150);
  displayPicture(ecran, 380, 150, "images/X.bmp");
  printNumber(20, ecran, 420, 150);
  //Vitesse
  displayPicture(ecran, 100, 250, "images/vitesse.bmp");
  displayPicture(ecran, 300, 250, "images/lent.bmp");
  displayPicture(ecran, 450, 250, "images/moyen.bmp");
  displayPicture(ecran, 600, 250, "images/rapide.bmp");
  //Objets
  displayPicture(ecran, 100, 350, "images/objets.bmp");
  displayPicture(ecran, 300, 350, "images/active.bmp");
  displayPicture(ecran, 500, 350, "images/desactive.bmp");
  //Flèche
  displayPicture(ecran, 50, (selected + 1) * 100 - 65, "images/fleche.bmp");
  //Affichage
  SDL_Flip(ecran);
}