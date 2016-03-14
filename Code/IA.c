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




direction aleatoire(serpent schlanga, plateau p) {
    int dir=rand()%4; //0=BAS, 1=HAUT, 2=GAUCHE, 3=DROITE
    position head=cree_position(schlanga->coordonnees->x, schlanga->coordonnees->y);
        if (dir==0) {
            head->x+=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else return BAS;
        }

        if (dir==1) {
            head->x+=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else {
                return HAUT;
            }
        }

        if (dir==2) {
            head->y-=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else {
                return GAUCHE;
            }
        }

        if (dir==3) {
            head->y+=1;
            if (etat_case(p,head)!=vide) {
                dir=rand()%4;
            }
            else {
                return DROITE;
            }
        }
    }


void defensif(serpent schlanga, plateau p) {
    int casesVides=0, i,j;
    position head=cree_position(schlanga->coordonnees->x, schlanga->coordonnees->y);
    if(schlanga->suivant->coordonnees->x==head->x+1) {

    }


}