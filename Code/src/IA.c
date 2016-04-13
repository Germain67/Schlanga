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
    srand(time(NULL));
    while(a == 1){
        int dir=rand()%4; //0=BAS, 1=HAUT, 2=GAUCHE, 3=DROITE
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
                printf("erreur plud de 100 repet");
                a = 0;
            }
        }
    }
    return dir1;
}

// IA défensif
direction IA_defensif_direction(direction last_deplacement, serpent schlanga, plateau p) {
	int scan=4;	
	int nb_case=0;
	int count[4]; // count[0] = HAUT - count[1] = BAS - count[2] = GAUCHE - count[3] = DROITE
	count[0]=0; count[1]=0; count[2]=0; count[3]=0;
	direction dir;
	int lar=p->largeur;
	int hau=p->hauteur;
	int y=schlanga->coordonnees->y;
	int x=schlanga->coordonnees->x;

	int i,j;

	// Cas en haut
	if (last_deplacement != BAS) {
		for (i=0;i<scan;i++) {
			y=y-1;
			nb_case=scan-i-1; // Le pas de case à regarder à gauche et à droite.
			if (y > 0 ) { // Si la nouvelle position est bien dans le tableau
				for (j=1;j<nb_case+1;j++) { // On itère sur le nombre de case à regarder de chaque côté
					if (x-j > 0) { // On regarde nb_case à gauche (si elles sont dans le plateau)
						if(p->data[x-j][y]->type == vide) { // Si elle est vide, on itère
							count[0] ++;
						}
					}
					if (x+j < lar) { // On regarde nb_case à droite (si elles sont dans le plateau)
						if (p->data[x+j][y]->type == vide) { // Si elle est vide, on itère
							count[0] ++;
						}
					}
				}
				if (p->data[x][y]->type == vide) { // On regarde la case courante
					count[0] ++;
				}
			}	
		}
	}

	y=schlanga->coordonnees->y;
	x=schlanga->coordonnees->x;

	// Cas en bas
	if (last_deplacement != HAUT) {
		for (i=0;i<scan;i++) {
			y=y+1;
			nb_case=scan-i-1; // Le pas de case à regarder à gauche et à droite.
			if (y < hau ) { // Si la nouvelle position est bien dans le tableau
				for (j=1;j<nb_case+1;j++) { // On itère sur le nombre de case à regarder de chaque côté
					if (x-j > 0) { // On regarde nb_case à gauche (si elles sont dans le plateau)
						if(p->data[x-j][y]->type == vide) { // Si elle est vide, on itère
							count[1] ++;
						}
					}
					if (x+j < lar) { // On regarde nb_case à droite (si elles sont dans le plateau)
						if (p->data[x+j][y]->type == vide) { // Si elle est vide, on itère
							count[1] ++;
						}
					}
				}
				if (p->data[x][y]->type == vide) { // On regarde la case courante
					count[1] ++;
				}
			}	
		}
	}

	y=schlanga->coordonnees->y;
	x=schlanga->coordonnees->x;

	// Cas à gauche
	if (last_deplacement != DROITE) {	
		for (i=0;i<scan;i++) {
			nb_case=scan-i-1; // Le pas de case à regarder en haut et en bas.
			x=x - 1; // On regarde à gauche
			if (x > 0) { // Si la nouvelle position est bien dans le tableau
				for (j=1;j<nb_case+1;j++) { // On itère sur le nombre de case à regarder de chaque côté (en haut ou en bas)
					if (y-j > 0) { // On regarde nb_case en haut (si elles sont dans le plateau)
						if(p->data[x][y-j]->type == vide) { // Si elle est vide, on itère
							count[2] ++;
						}
					}
					if (y+j < hau) { // On regarde nb_case en bas (si elles sont dans le plateau)
						if (p->data[x][y+j]->type == vide) { // Si elle est vide, on itère
							count[2] ++;
						}
					}
				}
				if (p->data[x][y]->type == vide) { // On regarde la case courante
					count[2] ++;
				}
			}	
		}
	}


	y=schlanga->coordonnees->y;
	x=schlanga->coordonnees->x;

	// Cas à droite
	if (last_deplacement != GAUCHE) {
		for (i=0;i<scan;i++) {
			nb_case=scan-i-1; // Le pas de case à regarder en haut et en bas.

			x=x + 1; // On regarde à droite
			if (x < lar) { // Si la nouvelle position est bien dans le tableau
				for (j=1;j<nb_case+1;j++) { // On itère sur le nombre de case à regarder de chaque côté (en haut ou en bas)
					if (y-j > 0) { // On regarde nb_case en haut (si elles sont dans le plateau)
						if(p->data[x][y-j]->type == vide) { // Si elle est vide, on itère
							count[3] ++;
						}
					}
					if (y+j < hau) { // On regarde nb_case en bas
						if (p->data[x][y+j]->type == vide) { // Si elle est vide, on itère
							count[3] ++;
						}
					}
				}
				if (p->data[x][y]->type == vide) { // On regarde la case courante
					count[3]++;
				}
			}	
		}
	}

	printf(" Haut : %d \n Bas : %d \n Gauche : %d \n Droite : %d \n \n", count[0], count[1], count[2], count[3]);

	// Récupérer le maximum
	int max=0;
	int max_atteint[4];
	for (i=0;i<4;i++) { // Calcul du max
		if (max < count[i]) {
			max=count[i];
		}
		max_atteint[i]=0;
	}

	int l=0;
	for (i=0;i<4;i++) { // On récupère le(s) direction(s) où le max est atteint
		if (max == count[i]) {
			max_atteint[l]=i;
			l++;
		}
	}
		

	srand(time(NULL));
	int val=rand()%l;

	if (max_atteint[val]==0) {
		dir=HAUT;
	}
	if (max_atteint[val]==1) {
		dir=BAS;
	}
	if (max_atteint[val]==2) {
		dir=GAUCHE;
	}
	if (max_atteint[val]==3) {
		dir=DROITE;
	}

	return dir;
}
