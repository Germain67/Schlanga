/**
 * \file      plateau.c
 * \date      19 avril 2016
 * \brief     Implémentation des fonctions relatives à la manipulation du plateau de jeu
 */


#include "plateau.h"
#include "snake.h"

/**
 * \fn       initPlateau
 * \brief    génère et alloue la mémoire d'un plateau de cases vides
 * \param    hauteur du plateau
 * \param    largeur du plateau
 * \return   plateau initialisé
 */


plateau initPlateau(int hauteur, int largeur){
	plateau p = (plateau) malloc(hauteur * largeur * sizeof(element) + 2 * sizeof(int));
	p->data = (element**) malloc(hauteur * sizeof(element*));
	int i;
	for(i = 0; i<hauteur ; i++){
		p->data[i] = (element*) malloc(largeur * sizeof(element));
		int j;
		for(j = 0; j<largeur; j++){
			p->data[i][j] = initElement(vide);
		}
	}
	p->hauteur = hauteur;
	p->largeur = largeur;
	return p;
}

/**
 * \fn       free_element
 * \brief    libère la mémoire de l'élément désigné en paramètre
 * \param    p  plateau où est placé l'élément
 * \param    x colonne de l'événement
 * \param    y  ligne de l'événement
 * \return   rien
 */


void free_element(plateau p, int x, int y) {
	free(p->data[x][y]);
}

/**
 * \fn       free_plateau
 * \brief    libère la mémoire allouée au plateau
 * \param    p  plateau à libérer
 * \return   rien
 */

void free_plateau(plateau p) {
	int h=p->hauteur;
	int l=p->largeur;
	int i;
	int j;
	for (i=0;i<h;i++) {
		for (j=0;j<l;j++) {
			free_element(p,i,j); // On free les element
		}
		free(p->data[i]); // On free les element*
	}
	free(p->data);
	free(p); // On free les element**
}

/**
* \fn       initMurs
* \brief    fonction qui place les murs sur les bords du plateau
* \param    p  plateau où il faut mettre les murs
* \return   rien
*/


void initMurs(plateau p){
	int x, y;
	for(x = 0; x < p->hauteur; x++){
		for(y = 0; y <p->largeur; y++){
			if(x == 0 || x == p->hauteur - 1 || y == 0 || y == p->largeur - 1){
				updateElement(mur,p->data[x][y]);
			}
		}
	}
}

/**
* \fn       addSerpentPlateau
* \brief    Ajoute le serpent au plateau en début de partie
* \param    s  serpent à placer
* \param    p  plateau où il faut placer le serpent
* \param   isSchlanga  entier qui indique si c'est un serpent ou un schlanga
* \return   rien
*/

// isSchlanga = 1 si c'est un Schlanga / 0 sinon
void addSerpentPlateau(serpent s, plateau p, int isSchlanga){
	serpent temp = s;
	while(temp != NULL){
		if (isSchlanga == 1) {
			updateElement(snake_schlanga,p->data[temp->coordonnees->x][temp->coordonnees->y]);
		}
		else {
			updateElement(snake,p->data[temp->coordonnees->x][temp->coordonnees->y]);
		}
		temp = temp->suivant;
	}
	free_serpent(temp);
}

/**
* \fn       updateSerpentPlateau
* \brief    met à jour le plateau après le déplacement du serpent
* \param    tete  tete du serpent
* \param    p  plateau où il faut placer le serpent
* \param    queue  position de la queue
* \param    isSchlanga entier qui indique si c'est un serpent ou un schlanga
* \return   rien
*/

void updateSerpentPlateau(serpent tete, plateau p, position queue, int isSchlanga){
	if(isSchlanga == 1){
		updateElement(snake_schlanga,p->data[tete->coordonnees->x][tete->coordonnees->y]);
	}
	else{
		updateElement(snake,p->data[tete->coordonnees->x][tete->coordonnees->y]);
	}
	updateElement(vide,p->data[queue->x][queue->y]);
}

/**
* \fn       collision
* \brief    gère les collisions du serpent avec les obstacles et les murs
* \param    p  plateau de jeu
* \param    d  direction de la case avec laquelle on veut tester la collision
* \param    s  serpent concerné par le test
* \return   retourne 1 s'il y collision, 0 sinon
*/


int collision(plateau p, direction d, serpent s){
	int x = s->coordonnees->x;
	int y = s->coordonnees->y;
	int b=0;	
	if (d==HAUT){
		y=y-1;
	}

	if (d==BAS){
		y=y+1;
	}
	
	if (d==DROITE){
		x=x+1;
    	}
    
	if (d==GAUCHE){
		x=x-1;
	}

	if (p->data[x][y]->type == snake ) {
		b=1;
	}
	if (p->data[x][y]->type == snake_schlanga ) {
		b=1;
	}
	if (p->data[x][y]->type == mur ) {
		b=1;
	}
	if (p->data[x][y]->type == objet ) {
		b=1;
	}
	return b;
}

int appartient_plateau(position p , plateau plat){
	int x = plat->largeur;
	int y = plat->hauteur;
	int x1 = p->x;
	int y1 = p->y;	
	if(x1 > 0 && x1 < x){
		if (y1 > 0 && y1 < y){
			return 1;
		}
	}
	else{
		return 0;
	}
}

int deadend(plateau p, direction d, serpent s){
	int x = s->coordonnees->x;
	int y = s->coordonnees->y;
	int b=0;
	position pos = cree_position((x+1),(y+2));
	position pos1 = cree_position((x+1),(y+1));
	position pos2 = cree_position((x+1),(y-1));
	position pos3 = cree_position((x-1),(y+1));
	position pos4 = cree_position((x-1),(y-1));
	if(d == DROITE)	{
		if ((appartient_plateau(pos1,p) == 1) && (appartient_plateau(pos2,p) == 1)){
			if (p->data[x+1][y-1]->type != vide && p->data[x+1][y+1]->type != vide){
				b = 1;
			}
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x+1][y-1]->type != vide && p->data[x+1][y+2]->type != vide){
					b = 1;
				}
			}
			pos->y = (y-2);
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x+1][y-2]->type != vide && p->data[x+1][y+1]->type != vide){
					b = 1;
				}
			}
		}
	}
	if (d == GAUCHE){
		if (appartient_plateau(pos3,p) == 1 && appartient_plateau(pos4,p) == 1){
			if (p->data[x-1][y-1]->type != vide && p->data[x-1][y+1]->type != vide){
				b = 1;
			}
			pos->x = (x-1);
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x-1][y-2]->type != vide && p->data[x-1][y+1]->type != vide){
					b = 1;
				}
			}
			pos->y = (y+2);
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x-1][y-1]->type != vide && p->data[x-1][y+2]->type != vide){
					b = 1;
				}
			}
		}
	}
	if (d == HAUT){
		if ((appartient_plateau(pos2,p) == 1) && (appartient_plateau(pos4,p) == 1)){
			if (p->data[x-1][y-1]->type != vide && p->data[x+1][y-1]->type != vide){
				b = 1;
			}
			pos->x = (x-2);
			pos->y = (y-1);
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x-2][y-1]->type != vide && p->data[x+1][y-1]->type != vide){
					b = 1;
				}
			}
			pos->x = (x+2);
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x-1][y-1]->type != vide && p->data[x+2][y-1]->type != vide){
					b = 1;
				}
			}
		}
	}
	if (d == BAS){
		if (appartient_plateau(pos1,p) == 1 && appartient_plateau(pos3,p) == 1){
			if (p->data[x-1][y+1]->type != vide && p->data[x+1][y+1]->type != vide){
				b = 1;
			}	
			pos->y = (y+1);
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x-1][y+1]->type != vide && p->data[x+2][y+1]->type != vide){
					b = 1;
				}
			}
			pos->x = (x-2);
			if (appartient_plateau(pos,p) == 1){
				if (p->data[x-2][y+1]->type != vide && p->data[x+1][y+1]->type != vide){
					b = 1;
				}
			}
		}
	}
	return b;
}
