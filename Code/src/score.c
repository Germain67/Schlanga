//
// Created by lise on 10/05/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "score.h"


/** gere un evenement 'clavier' et rajoute ce qu'il faut dans la chaine
     passée en paramètre, à la position pos.

     retourne la nouvelle pos  **/
/*int gereTouche(SDL_KeyboardEvent *keyevent, char * chaine, int pos)
{
    switch(keyevent.keysym.sym)
    {
        case SDLK_RETURN:
            //C'est la touche entrée, chacun gère ca comme il veut
            return pos;
        case SDLK_BACKSPACE:
            //Retour en arrière
            if (pos > 0) {
                chaine[--pos] = 0;
            }
            return pos;
        case SDLK_TAB:
            //Tab, on insère 4 espaces
        {
            int posmax;
            for (posmax=pos+4; pos < posmax; pos++) {
                chaine[pos] = ' ';
            }
            chaine[pos] = 0;
            return pos;
        }
            //Il y a d'autres cas spéciaux à gérer...
        default:
            break;
    }
    //Là on attaque les caractères tapés
    if (keyevent.keysym.unicode != 0)
    {
        chaine[pos++] = keyevent.keysym.unicode;
        chaine[pos] = 0;
    }
    return pos;
}
*/

/*int main(...)
{
    char chaine[20+1];
    int curpos = 0;
    ...
    SDL_EnableUNICODE(SDL_Enable);
    ...

    //boucle qui gère les events
    while(...)
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                curpos = gereTouche(&(event.key), chaine, curpos);
                break;
                ....
        }
        ...
    }
    ...
}*/

void Gameover(int compteur, char* mess) {
    SDL_Surface *ecran = NULL, *texte = NULL, *fond = NULL, *gameover;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    int continuer = 1;
    char scores[20] = ""; /* Tableau de char suffisamment grand */

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Fin du jeu !", NULL);


    fond = IMG_Load("sable.jpg");

    /* Chargement de la police */
    police = TTF_OpenFont("angelina.ttf", 65);

    /* Initialisation du temps et du texte */
    sprintf(scores, "Votre score : %d", compteur);
    gameover = TTF_RenderText_Blended(police, mess, couleurNoire);
    texte = TTF_RenderText_Blended(police, scores, couleurNoire);

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
                    default:
                        break;
                }
                break;
            default:
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));




        sprintf(scores, "Score : %d", compteur); /* On écrit dans la chaîne "temps" le nouveau temps */

        // Blit du fond
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond, NULL, ecran, &position); /* Blit du fond */



        position.x = 180;
        position.y = 210;
        SDL_BlitSurface(texte, NULL, ecran, &position);/* Blit du texte */
        SDL_Flip(ecran);

        position.x = 180;
        position.y = 110;
        SDL_BlitSurface(gameover, NULL, ecran, &position);/* Blit du texte */
        SDL_Flip(ecran);
    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    //SDL_Quit();


}

int live_scores ()
{
    SDL_Surface *ecran=NULL, *texte = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    int continuer = 1;
    int tempsActuel2 = 0, tempsPrecedent = 0, compteur = 0;
    char temps[20] = ""; /* Tableau de char suffisamment grand */

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Scores", NULL);

    /* Chargement de la police */
    police = TTF_OpenFont("Industrial Poison.ttf", 65);

    /* Initialisation du temps et du texte */
    tempsActuel2 = SDL_GetTicks();
    sprintf(temps, "Temps : %d", compteur);
    texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche);

    while (continuer) {
        SDL_PollEvent(&event);
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
                break;
            default:
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        tempsActuel2 = SDL_GetTicks();
        if (tempsActuel2 - tempsPrecedent >= 100) /* Si 100 ms au moins se sont écoulées */
        {
            compteur += 10; /* On rajoute 100 ms au compteur */
            sprintf(temps, "Score : %d", compteur); /* On écrit dans la chaîne "temps" le nouveau temps */
            SDL_FreeSurface(texte); /* On supprime la surface précédente */
            texte = TTF_RenderText_Shaded(police, temps, couleurNoire,
                                          couleurBlanche); /* On écrit la chaîne temps dans la SDL_Surface */
            tempsPrecedent = tempsActuel2; /* On met à jour le tempsPrecedent */
        }

        position.x = 10;
        position.y = 10;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);

    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_Quit();

    return compteur;
}

int main(int argc, char *argv[]) {
    int compteur=live_scores();
    char mess[20];
    sprintf(mess, "Vous avez perdu !");
    Gameover(compteur, mess);
    return 0;
}
