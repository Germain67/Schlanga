/**
 * \file      IA.c
 * \date      19 avril 2016
 * \brief     implémentation des différentes intelligences artificielles qui pilotent le schlanga
 */

#include "IA.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "element.h"
#include "plateau.h"



/**
 * \fn       aleatoire
 * \brief    dirige le schlanga en lui faisant adopter un comportement aléatoire
 * \param    param1  schlanga (serpent à diriger)
 * \param    param2  plateau sur lequel on joue
 * \return   direction dans laquelle doit aller le schlanga
 */

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

/**
 * \fn       int_to_dir
 * \brief    transforme un entier en une direction selon une convention prédéfinie
 * \param    param1  entier à transformer
 * \return   direction correspondant à l'entier donné en paramètre
 */

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

/**
 * \fn       IA_défensif_direction
 * \brief    dirige le schlanga en lui faisant adopter un comportement défensif
 * \details  le schlanga se dirige vers les zones où il n'y a pas de serpent ni d'obstacle
 * \param    param1  schlanga (serpent à diriger)
 * \param    param2  plateau sur lequel on joue
 * \return   direction dans laquelle doit aller le schlanga
 */

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

direction IA_agressif_direction(serpent schlanga, serpent snake, plateau p) { 
	direction dir;
	direction dirsnake;
	position cible;
	int y=schlanga->coordonnees->y;
	int x=schlanga->coordonnees->x;
	serpent S = snake->suivant;
	int y1=snake->coordonnees->y;
	int x1=snake->coordonnees->x;
	int y2=S->coordonnees->y;
	int x2=S->coordonnees->x;

	if(x1 == x2){
		if(y1 > y2){
			dirsnake = BAS;
			cible =  cree_position(x1, (y1 + 2));
			if (appartient_plateau(cible,p) == 0){
				cible = snake->coordonnees;
			}
		}
		else{
			dirsnake = HAUT;
			cible =  cree_position(x1, (y1 - 2));
			if (appartient_plateau(cible,p) == 0){
				cible = snake->coordonnees;
			}
		}
	}
	else{
		if(x1 > x2){
			dirsnake = DROITE;
			cible =  cree_position((x1 + 2), y1);
			if (appartient_plateau(cible,p) == 0){
				cible = snake->coordonnees;
			}
		}
		else{
			dirsnake = GAUCHE;
			cible =  cree_position((x1 - 2), y1);
			if (appartient_plateau(cible,p) == 0){
				cible = snake->coordonnees;
			}
		}
	}

	y1=cible->y;
	x1=cible->x;
	if (cible != schlanga->coordonnees && appartient(cible, schlanga) == 0){	
		if(x<x1 && y<y1){
			if (dirsnake == HAUT){
				dir = DROITE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = BAS;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = HAUT;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == GAUCHE){
				dir = BAS;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = DROITE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = HAUT;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == BAS){
				dir = BAS;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = DROITE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = HAUT;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == DROITE){
				dir = DROITE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = BAS;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = HAUT;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}	
		}
		if(x<x1 && y>y1){
			if (dirsnake == HAUT){
				dir = HAUT;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = DROITE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}	
			if(dirsnake == GAUCHE){
				dir = HAUT;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = DROITE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == BAS){
				dir = DROITE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = HAUT;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}	
			if(dirsnake == DROITE){
				dir = DROITE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = HAUT;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
		}
		if(x>x1 && y<y1){
			if (dirsnake == HAUT){
				dir = GAUCHE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = BAS;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = HAUT;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == GAUCHE){
				dir = GAUCHE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = BAS;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = HAUT;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == BAS){
				dir = BAS;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = GAUCHE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = HAUT;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == DROITE){
				dir = BAS;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = GAUCHE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0|| deadend(p, dir, schlanga) != 0){
							dir = HAUT;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
		}	
		if(x>x1 && y>y1){
			if (dirsnake == HAUT){
				dir = HAUT;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = GAUCHE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0|| deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == GAUCHE){
				dir = GAUCHE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = HAUT;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0|| deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == BAS){
				dir = GAUCHE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = HAUT;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
			if(dirsnake == DROITE){
				dir = HAUT;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = GAUCHE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = BAS;
							if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
								dir = IA_defensif_direction(schlanga,p);
							}
						}		
					}
				}
			}
		}
		if(x==x1 && y<y1){
			dir = BAS;
			if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
				dir = GAUCHE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = DROITE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = HAUT;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = IA_defensif_direction(schlanga,p);
						}
					}		
				}
			}
		}
		if(x==x1 && y>y1){
			dir = HAUT;
			if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
				dir = GAUCHE;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = DROITE;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = BAS;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = IA_defensif_direction(schlanga,p);
						}
					}		
				}
			}
		}
		if(x<x1 && y==y1){
			dir = DROITE;
			if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
				dir = BAS;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = HAUT;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = GAUCHE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = IA_defensif_direction(schlanga,p);
						}
					}		
				}
			}
		}
		if(x>x1 && y==y1){
			dir = GAUCHE;
			if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
				dir = HAUT;
				if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
					dir = BAS;
					if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
						dir = DROITE;
						if (collision(p,dir,schlanga)!=0 || deadend(p, dir, schlanga) != 0){
							dir = IA_defensif_direction(schlanga,p);
						}
					}		
				}
			}
		}
	}
	else{
		if(cible != schlanga->coordonnees){

		}
		else{
			
		}
	}
	return dir;
}