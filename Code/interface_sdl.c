#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <unistd.h>

int dir = 0;
int count = 0;

void showRectangle(SDL_Surface* ecran, int x, int y, int size, int height){
  SDL_Surface *rectangle = NULL;
  SDL_Rect position;
   // Allocation de la surface
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, size, height, 32, 0, 0, 0, 0);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
    position.x = x;
    position.y = y;
    // Remplissage de la surface avec du blanc
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(rectangle, NULL, ecran, &position); // Collage de la surface sur l'écran

}

int main(int argc, char *argv[])
{
  int continuer = 1;
  SDL_Surface *ecran = NULL;
  SDL_Event event;
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

  // Activation de la répétition des touches
  SDL_EnableKeyRepeat(100, 100);

  while (continuer)
  {
    SDL_WaitEvent(&event);
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
                    dir = 0;
                    break;
                case SDLK_DOWN:
                    dir = 1;
                    break;
                case SDLK_RIGHT:
                    dir = 2;
                    break;
                case SDLK_LEFT:
                    dir = 3;
                    break;
            }
            break;
    }
    usleep(100000);
    count += 1;
    if(count%500 == 0){
      //move(dir);
    }

    // Effacement de l'écran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    //On recrée la surface
    showRectangle(ecran,50,50,20,20);
    showRectangle(ecran,70,70,20,20);
    SDL_Flip(ecran);
  }

  // Désactivation de la répétition des touches (remise à 0)
  SDL_EnableKeyRepeat(0, 0);

  return 0;
}
