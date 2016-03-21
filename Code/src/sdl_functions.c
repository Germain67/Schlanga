#include "sdl_functions.h"

void showRectangle(SDL_Surface* ecran, int x, int y, int size, int height, Uint32 R, Uint32 G, Uint32 B){
  SDL_Surface *rectangle = NULL;
  SDL_Rect position;
  // Allocation de la surface
  rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, size, height, 32, R, G, B, 0);
  position.x = x;
  position.y = y;
  SDL_BlitSurface(rectangle, NULL, ecran, &position); // Collage de la surface sur l'écran
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
        showRectangle(ecran,x*20,y*20,15,15, 0, 100, 0);
      }
      //Noir pour un mur
      else if(currentCase->type == mur){
        showRectangle(ecran,x*20,y*20,15,15, 0, 0, 0);
      }
      //Rouge pour le schlanga
      else if(currentCase->type == snake_schlanga){
        showRectangle(ecran,x*20,y*20,15,15, 100, 0, 0);
      }
    }
  }
  SDL_Flip(ecran);
}