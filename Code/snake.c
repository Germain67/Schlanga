#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

serpent init_serpent(serpent suivant, position pos) {
	serpent s = (serpent) malloc(sizeof(struct serpent));
    s->coordonnees = pos;
    s->suivant = suivant;
	return s;
}

position cree_position(int x, int y) {
    position p = NULL;
    p = (position) malloc(sizeof(position));
    p->x = x;
    p->y = y;
    return p;
}

/*ajout element a la tete du snake*/

serpent ajout_entete(serpent s, position p){
    return init_serpent(s, p);
}

/*eliminer le dernier element du snake*/

void suppression_queue(serpent s){
    serpent courant = s;
    serpent precedent = NULL;
    while (courant->suivant !=NULL) {
       precedent = courant;
       courant = courant->suivant;
    }
    precedent->suivant = NULL;
    free_serpent(courant);
}

serpent free_serpent(serpent s) {
    serpent tmp = s;
    serpent next;
    while (tmp != NULL) {
        next=tmp->suivant;
        free(tmp);
        tmp=next;
    }
    return NULL;
}


/*deplacement*/

void deplacement(direction d, serpent s){
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
    s = ajout_entete(s,p);    
    
    //On supprime la queue
    suppression_queue(s);
}

