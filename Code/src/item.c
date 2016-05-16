#include "item.h"
#include <stdlib.h>
#include <time.h>

int nb_item_created;

/**
 * \fn         create_item
 * \brief      Permet la création d'un item sur le plateau si les conditions sont réalisées
 * \param      plateau p où l'item sera généré.
 * \param      int nb qui indique le nombre d'items déjà présent.
 * \return     rien
 */
void create_item(plateau p, int nb) {
	int x,y;
	int b=0;
	nb_item_created=nb;	
	while (b!=1){
		x=(rand() % p->largeur);
		y=(rand() % p->hauteur);
		if (p->data[x][y]->type == vide) {
			b=1;
		}
	}	
	int type = (rand() % 5);
	if (type==0 && nb_item_created < 4) {
		p->data[x][y]->type = grandir;
		nb_item_created ++;
	}
	else if (type==1 && nb_item_created < 4) {
		p->data[x][y]->type = reduire;
		nb_item_created ++;
	}
	else if (type==2 && nb_item_created < 4) {
		p->data[x][y]->type = accelerer;
		nb_item_created ++;
	}
	else if (type==3 && nb_item_created < 4) {
		p->data[x][y]->type = ralentir;
		nb_item_created ++;
	}
	else if (type==4) {
		if (collision_coord(p,x+1,y)==0 && collision_coord(p,x-1,y)==0 && collision_coord(p,x,y-1)==0 && collision_coord(p,x,y+1)==0) {
			p->data[x][y]->type = mur;
		}
	}
}

/**
 * \fn       updateNbItem_created
 * \brief    permet de mettre à jour le nombre d'item quand un item est crée
 * \return   vitesse mise à jour
 */
int updateNbItem_created () {
	return nb_item_created;
}

/**
* \fn       deplacement_grandir
* \brief    fonction utilisée pour déplacer le serpent ou le schlanga lorsqu'elle rencontre l'item grandir
* \param    d  direction dans laquelle on veut déplacer le serpent
* \param    s  serpent à déplacer
* \param    type  serpent ou schlanga
* \return   serpent déplacé
*/

serpent deplacement_grandir(direction d, serpent s){
    position p;
    int x = s->coordonnees->x;
    int y = s->coordonnees->y;
    //On met à jour les coordonnées
    if (d==HAUT){
	p=cree_position(x,y - 1);
    }
    if (d==BAS){
	p=cree_position(x,y + 1);
    }
    if (d==DROITE){
	p=cree_position(x + 1,y);
    }
    if (d==GAUCHE){
	p=cree_position(x - 1,y);
    }
    return ajout_entete(s,p);    
}

/**
* \fn       deplacement_reduire
* \brief    fonction utilisée pour déplacer le serpent ou le schlanga lorsqu'elle rencontre l'item reduire
* \param    d  direction dans laquelle on veut déplacer le serpent
* \param    s  serpent à déplacer
* \param    type  serpent ou schlanga
* \return   serpent déplacé
*/
serpent deplacement_reduire(direction d, serpent s){
    position p;
    int x = s->coordonnees->x;
    int y = s->coordonnees->y;
    //On met à jour les coordonnées
    if (d==HAUT){
	p=cree_position(x,y - 1);
    }
    if (d==BAS){
	p=cree_position(x,y + 1);
    }
    if (d==DROITE){
	p=cree_position(x + 1,y);
    }
    if (d==GAUCHE){
	p=cree_position(x - 1,y);
    }
    //On supprime 2 fois la queue
    suppression_queue(s);
    return ajout_entete(s,p);    
}
