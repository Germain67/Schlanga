/**
 * \file      snake.c
 * \date      19 avril 2016
 * \brief     implémentation des fonctions de base relatives au serpent ou au schlanga
 *
 */

#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

/**
* \fn       cree_position
* \brief    initialise et alloue la mémoire nécessaire à une position
* \param    x  coordonnée x
* \param    y  coordonnée y
* \return   position initialisée
*/
position cree_position(int x, int y) {
    position p = NULL;
    p = (position) malloc(sizeof(position));
    p->x = x;
    p->y = y;
    return p;
}

/**
* \fn       ajout_entete
* \brief    ajoute une position en tête du serpent
* \param    suivant  serpent
* \param    pos  position à ajouter en tête
* \return   serpent avec nouvelle position en tête
*/

serpent ajout_entete(serpent suivant, position pos){
    serpent s = (serpent) malloc(sizeof(struct serpent));
    s->coordonnees = pos;
    s->suivant = suivant;
    return s;
}

/**
* \fn       get_position_queue
* \brief    récupère la position de la queue du serpent
* \param    s  serpent
* \return   coordonnées de la queue
*/
position get_position_queue(serpent s){
    serpent courant = s;
    while (courant->suivant !=NULL) {
       courant = courant->suivant;
    }
    free(courant->suivant);
    return courant->coordonnees;
}

/**
* \fn       suppression_queue
* \brief    supprime la queue du serpent (dernier élément)
* \param    s  serpent
* \return   rien
*/
void suppression_queue(serpent s){
    serpent courant = s;
    serpent precedent = NULL;
    while (courant->suivant !=NULL) {
       precedent = courant;
       courant = courant->suivant;
    }
    precedent->suivant = NULL;
}

/**
* \fn       free_serpent
* \brief    libère la mémoire allouée au serpent
* \param    s  serpent
* \return   pointeur NULL
*/

serpent free_serpent(serpent s) {
    serpent tmp = s;
    serpent next;
    while (tmp != NULL) {
        next=tmp->suivant;
	free(tmp->coordonnees);
        free(tmp);
        tmp=next;
    }
    return NULL;
}


/**
* \fn       free_position
* \brief    libère alloue la mémoire allouée à une position
* \param    pos  position pos à libérer
* \return
*/

void free_position(position pos) {
    free(pos);
}

/**
* \fn       init_serpent
* \brief    crée le serpent, pos_init est la queue du serpent initialisé
* \param    taille  taille du serpent (entier)
* \param    pos_init  position de la queue
* \param    dir direction dans laquelle on veut orienter le serpent
* \return   serpent dont les positions sont bien placées sur le plateau
*/
serpent init_serpent(int taille, position pos_init, direction dir)  {
    serpent s = NULL;

    int i;

    position pos_suiv;
    s = ajout_entete(s,pos_init);
    if (dir == HAUT){
        for (i=0;i<taille;i++){
            pos_suiv = cree_position(pos_init->x,pos_init->y - i);
            s = ajout_entete(s,pos_suiv);
        }
   }
   if (dir == BAS){
        for (i=0;i<taille;i++){
            pos_suiv = cree_position(pos_init->x,pos_init->y + i);
            s = ajout_entete(s,pos_suiv);
        }
   }
   if (dir == DROITE){
        for (i=0;i<taille;i++){
            pos_suiv = cree_position(pos_init->x + i,pos_init->y);
            s = ajout_entete(s,pos_suiv);
        }
   }
   if (dir == GAUCHE){
        for (i=0;i<taille;i++){
            pos_suiv = cree_position(pos_init->x - i,pos_init->y);
            s = ajout_entete(s,pos_suiv);
        }
   }

   return s;
}


/**
* \fn       deplacement
* \brief    fonction utilisée pour déplacer le serpent ou le schlanga
* \param    d  direction dans laquelle on veut déplacer le serpent
* \param    s  serpent à déplacer
* \return   serpent déplacé
*/

serpent deplacement(direction d, serpent s){
    position p;
    //On met à jour les coordonnées
    if (d==HAUT){
	p=cree_position(s->coordonnees->x,s->coordonnees->y - 1);
    }
    if (d==BAS){
	p=cree_position(s->coordonnees->x,s->coordonnees->y + 1);
    }
    if (d==DROITE){
	p=cree_position(s->coordonnees->x + 1,s->coordonnees->y);
    }
    if (d==GAUCHE){
	p=cree_position(s->coordonnees->x - 1,s->coordonnees->y);
    }
    //On supprime la queue
    suppression_queue(s);
    return ajout_entete(s,p);    
}

int appartient(position x, serpent l){
    if ( l == NULL ) return(0);
    if ( x == l->coordonnees ) return(1);
    return(appartient(x, l->suivant));
}



