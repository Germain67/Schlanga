/**
 * \file      sdl_functions.c
 * \date      19 avril 2016
 * \brief     Fonctions utilisant la librairie SDL 
              servant à afficher le menu, le plateau de jeu et les images
 *
 */
#include "sdl_functions.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

/**
* \fn       displayPicture
* \brief    Fonction chargée de l'affichage d'une image a la position x,y de la fenetre
* \param    *ecran : Pointeur vers l'écran
* \param    x : Position de l'image en x
* \param    y : Position de l'image en y
* \param    *file : Pointeur vers le fichier contenant l'image
*/

int* tailleSnake;
int* taille_plateau;
int* speed;
int* objectActivated;
int* difficulte;

void initOptions(int* tailleS, int* tailleP, int* vitesse, int* objets, int* diff){
  tailleSnake = tailleS;
  taille_plateau = tailleP;
  speed = vitesse;
  objectActivated = objets; 
  difficulte = diff;
}

void displayPicture(SDL_Surface* ecran, int x, int y, char* file){
  SDL_Rect position;
  position.x = x;
  position.y = y;
  SDL_Surface *image = NULL;
  /* On charge l'image : */
  image = SDL_DisplayFormat(SDL_LoadBMP(file));
  /* Transparence */
  SDL_SetColorKey(image, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0, 0, 0));
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
      displayPicture(ecran, x*25, y*25, "images/vide.bmp");

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

void showLiveScore(SDL_Surface *ecran, int time, int score, int l)
{
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    char temps[20] = ""; /* Tableau de char suffisamment grand */

    /* Chargement de la police */
    police = TTF_OpenFont("fonts/poison.ttf", 20);

    /* Initialisation du temps et du texte */
    sprintf(temps, "Temps : %d", time);
    texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche);
    position.x = 15*(l+2);
    position.y = 0;
    SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
    SDL_FreeSurface(texte); /* On supprime la surface précédente */

    sprintf(temps, "Score : %d", score); /* On écrit dans la chaîne "temps" le nouveau temps */
    texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche); /* On écrit la chaîne temps dans la SDL_Surface */

    position.x = 20*(l+2);
    position.y = 0;
    SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
    SDL_Flip(ecran);

    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
}

void Gameover(SDL_Surface *ecran, int compteur, char* mess) {
    SDL_Surface *texte = NULL, *fond = NULL, *gameover;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    char scores[20] = ""; /* Tableau de char suffisamment grand */
    fond = IMG_Load("images/sable.jpg");

    /* Chargement de la police */
    police = TTF_OpenFont("fonts/angelina.ttf", 65);

    /* Initialisation du temps et du texte */
    sprintf(scores, "Votre score : %d", compteur);
    gameover = TTF_RenderText_Blended(police, mess, couleurNoire);
    texte = TTF_RenderText_Blended(police, scores, couleurNoire);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    sprintf(scores, "Score : %d", compteur); /* On écrit dans la chaîne "temps" le nouveau temps */
    // Blit du fond
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(fond, NULL, ecran, &position); 
    /* Blit du fond */
    position.x = 180;
    position.y = 210;
    SDL_BlitSurface(texte, NULL, ecran, &position);
    /* Blit du texte */
    SDL_Flip(ecran);
    position.x = 180;
    position.y = 110;
    SDL_BlitSurface(gameover, NULL, ecran, &position);
    /* Blit du texte */
    SDL_Flip(ecran);
    //Liberation des resources
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
}

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

void displayOptions(SDL_Surface* ecran, int selected, int selectedColumn){
  // Effacement de l'écran
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  //Mise à jour des options
  if(selected == 0){
    int newval = *tailleSnake + selectedColumn;
    if(newval >= 2 && newval <= *taille_plateau / 2)
    {
      *tailleSnake = newval;
    }
  }
  else if(selected == 1){
    int newval = *taille_plateau + selectedColumn;
    if(newval >= 10 && newval <= 30)
    {
      *taille_plateau = newval;
      if(*tailleSnake > newval/2){
        *tailleSnake -= 1;
      }
    }
  }
  else if(selected == 2){
    *speed += selectedColumn;
  }
  else if(selected == 3){
    *objectActivated += selectedColumn;
  }
  else if(selected == 4){
    *difficulte += selectedColumn;
  }
  //Serpent
  displayPicture(ecran, 100, 50, "images/taille.bmp");
  printNumber(*tailleSnake, ecran, 300, 50);
  //Plateau
  displayPicture(ecran, 100, 150, "images/plateau.bmp");
  printNumber(*taille_plateau, ecran, 300, 150);
  displayPicture(ecran, 380, 150, "images/X.bmp");
  printNumber(*taille_plateau, ecran, 420, 150);
  //Vitesse
  displayPicture(ecran, 100, 250, "images/vitesse.bmp");
  displayPicture(ecran, 300, 250, "images/lent.bmp");
  displayPicture(ecran, 450, 240, "images/moyen.bmp");
  displayPicture(ecran, 600, 250, "images/rapide.bmp");
  //Objets
  displayPicture(ecran, 100, 350, "images/objets.bmp");
  displayPicture(ecran, 300, 350, "images/active.bmp");
  displayPicture(ecran, 500, 350, "images/desactive.bmp");
  //IA
  displayPicture(ecran, 100, 440, "images/ia.bmp");
  displayPicture(ecran, 300, 440, "images/facile.bmp");
  displayPicture(ecran, 450, 440, "images/moyen.bmp");
  displayPicture(ecran, 600, 440, "images/difficile.bmp");
  //Valider
  displayPicture(ecran, 300, 550, "images/valider.bmp");
  //Flèche
  displayPicture(ecran, 50, (selected + 1) * 100 - 65, "images/fleche.bmp");
  //Rectangles de sélection vitesse
  if(*speed%3 == 0){
    displayPicture(ecran, 300, 250, "images/selection.bmp");
  }
  else if(*speed%3 == 1){
    displayPicture(ecran, 450, 250, "images/selection.bmp");
  }
  else{
    displayPicture(ecran, 600, 250, "images/selection.bmp");
  }
  //Rectangles de sélection objets
  if(*objectActivated%2 == 0){
    displayPicture(ecran, 300, 350, "images/selection.bmp");
  }
  else{
    displayPicture(ecran, 500, 350, "images/selection.bmp");
  }
  //Rectangles de sélection IA
  if(*difficulte%3 == 0){
    displayPicture(ecran, 300, 450, "images/selection.bmp");
  }
  else if(*difficulte%3 == 1){
    displayPicture(ecran, 450, 450, "images/selection.bmp");
  }
  else{
    displayPicture(ecran, 600, 450, "images/selection.bmp");
  }
  //Affichage
  SDL_Flip(ecran);
}