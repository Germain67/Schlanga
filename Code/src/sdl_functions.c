#include "sdl_functions.h"

void displayPicture(SDL_Surface* ecran, int x, int y, char* file){
  SDL_Rect position;
  position.x = x;
  position.y = y;
  SDL_Surface *image = NULL;
  /* On charge l'image : */
  image = SDL_LoadBMP(file);
  /* Transparence */
  SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0, 0, 0));
  /* On blitte l'image maintenant transparente sur le fond : */
  SDL_BlitSurface(image, NULL, ecran, &position);
  SDL_FreeSurface(image);
}

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
