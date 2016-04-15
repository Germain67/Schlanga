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
    direction dir1;
    // On définit les positions possibles que l'on va stocké dans un tableau
    int pos_possible[4];
    pos_possible[0]=-1; pos_possible[1]=-1; pos_possible[2]=-1; pos_possible[3]=-1; // Initialisation à -1
    int l=0; // Compteur de directions possibles
    if (collision(p,BAS,schlanga) == 0){ 
      pos_possible[l]=0; // BAS = 0
	    l++;
    }
    if (collision(p,HAUT,schlanga) == 0){ 
      pos_possible[l]=1; // HAUT = 1
	    l++;
    }
    if (collision(p,GAUCHE,schlanga) == 0){ 
      pos_possible[l]=2; // GAUCHE = 2
	    l++;
    }
    if (collision(p,DROITE,schlanga) == 0){ 
      pos_possible[l]=3; // DROITE = 3
	    l++;
    }
    if (l==0) { // Le schlanga ne peut plus se déplacer, il a perdu, il nous suffit de lui donner une direction aléatoire
	    pos_possible[l]=0;
    }

    //srand(time(NULL));
    int dir=rand()%l; // Nous avons l directions possibles, nous en choisissons une.

    if (pos_possible[dir]==0) {
        dir1 = BAS;
    }
    if (pos_possible[dir]==1) {
    	dir1 = HAUT;
    }
    if (pos_possible[dir]==2) {
        dir1 = GAUCHE;
    }
    if (pos_possible[dir]==3) {
        dir1 = DROITE;
    }

    return dir1;
}

direction int_to_dir(int i){
	if(i == 0){
		return HAUT;
	}
	else if(i == 1){
		return BAS;
	}
	else if(i == 2){
		return GAUCHE;
	}
	else{
		return DROITE;
	}
}

// IA défensif
direction IA_defensif_direction(serpent schlanga, plateau p) {
	int scan=4;	
	int nb_case=0;
	int count[4]; 
	direction dir;
	int lar=p->largeur;
	int hau=p->hauteur;
	int y=schlanga->coordonnees->y;
	int x=schlanga->coordonnees->x;
	

	int i,j;

	//count[0] = HAUT - count[1] = BAS - count[2] = GAUCHE - count[3] = DROITE
	count[0]=-1; 
	count[1]=-1; 
	count[2]=-1; 
	count[3]=-1;

	// Cas en haut
	if (collision(p,HAUT,schlanga)==0) {
		for (i=0;i<scan;i++) {
			y=y-1;
			nb_case=scan-i-1; // Le pas de case à regarder à gauche et à droite.
			if (y > 0 ) { // Si la nouvelle position est bien dans le tableau
				if (p->data[x][y]->type == vide) { // On regarde la case courante
					count[0] ++;
				}
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
			}	
		}
	}

	

	// Cas en bas
	if (collision(p,BAS,schlanga)==0) {
		y=schlanga->coordonnees->y;
		x=schlanga->coordonnees->x;
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



	// Cas à gauche
	if (collision(p,GAUCHE,schlanga)==0) {
		y=schlanga->coordonnees->y;
		x=schlanga->coordonnees->x;	
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

	// Cas à droite
	if (collision(p,DROITE,schlanga)==0) {
		y=schlanga->coordonnees->y;
		x=schlanga->coordonnees->x;
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

	/* DEBUG
	printf(" Haut : %d \n Bas : %d \n Gauche : %d \n Droite : %d \n \n", count[0], count[1], count[2], count[3]);
	*/

	if (count[0]==-1 && count[1]==-1 && count[2]==-1 && count[3]==-1) 
	{ 
		// Le schlanga ne peut plus se déplacer, il va se suicider
		dir=GAUCHE; 
	}
	else {
		// Récupérer le maximum
		int max=0;
		int max_atteint[4];
		for (i=0;i<4;i++) { // Calcul du max
			if (max < count[i]) {
				max = count[i];
			}
			max_atteint[i]=0; // On initialise max_atteint
		}

		int l=0;
		for (i=0;i<4;i++) { // On récupère le(s) direction(s) où le max est atteint et le nombre de positions pour laquelle le max est atteint
			if (max == count[i]) {
				max_atteint[l]=i;
				l++;
			}
		}
		
		srand(time(NULL));
		int val=rand()%l;

		dir = int_to_dir(max_atteint[val]);
	}
	
	return dir;
}
