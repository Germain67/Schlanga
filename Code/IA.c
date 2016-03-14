//
// Created by lise on 07/03/16.
//

#include "IA.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "element.h"
#include "plateau.h"

//Dirige le Schlanga dans une direction aléatoire




void aleatoire(serpent schlanga, plateau p) {
    int dir=rand()%4; //0=BAS, 1=HAUT, 2=GAUCHE, 3=DROITE
    position head=cree_position(schlanga->coordonnees->x, schlanga->coordonnees->y);
    while(1){
        if (dir==0) {
            head->x+=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else {
                deplacement(BAS, schlanga);
            }
        }

        if (dir==1) {
            head->x+=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else {
                deplacement(HAUT, schlanga);
            }
        }

        if (dir==2) {
            head->y-=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else {
                deplacement(GAUCHE, schlanga);
            }
        }

        if (dir==3) {
            head->y+=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else {
                deplacement(DROITE, schlanga);
            }
        }
    }
}

