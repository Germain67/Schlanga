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
    int a = 1;
    int b = 0;
    direction dir1;
    while(a == 1){
        int dir=rand()%4; //0=BAS, 1=HAUT, 2=GAUCHE, 3=DROITE
        position head=cree_position(schlanga->coordonnees->x, schlanga->coordonnees->y);
        if (dir==0) {
            dir1 = BAS;
        }
        if (dir==1) {
            dir1 = HAUT;
        }
        if (dir==2) {
            dir1 = GAUCHE;
        }
        if (dir==3) {
            dir1 = DROITE;
        }
        if (collision(p,dir1,schlanga) == 0){
            a = 0;
        }
        else {
            b = b + 1;
            if (b > 100){
                a = 0;
            }
        }
    }
    return dir1;
}


/*void defensif(serpent schlanga, plateau p) {
    int casesVides=0, i,j;
    position head=cree_position(schlanga->coordonnees->x, schlanga->coordonnees->y);
    if(schlanga->suivant->coordonnees->x==head->x+1) {

    }


}*/