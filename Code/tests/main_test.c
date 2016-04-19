/**
 * \file      main_test.c
 * \date      19 avril 2016
 * \brief     Test des fuites de mémoire sous Valgrind.
 */

#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/element.h"
#include "../src/plateau.h"
#include "../src/snake.h"
#include "../src/jeux.h"
#include "../src/test.h"
#include "../src/sdl_functions.h"

int main() {
	plateau p;
	int lon=25, lar=25, t=10; // Test avec un plateau de taille 25*25 et des serpents de taille 10

	p=initJeu(lon, lar, t); // Initialisation d'un plateau 25*25 avec des serpents de taille 10

	int etatPartie = 0; 
	p=updateJeu (p, HAUT, &etatPartie); // Mise à jour d'un plateau vers le jeu
	fin_de_partie_serpent();
	free_plateau(p);

	return 0;
}
