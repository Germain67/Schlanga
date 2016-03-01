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
    //On supprime la queue
    suppression_queue(s);
    position p;
    position c;
    c = s->coordonnees;
    //On met à jour les coordonnées
    if (d==BAS){
        p->x = c->x;
        p->y = c->y - 1;
        s = ajout_entete(s,p);
    }
    if (d==HAUT){
        p->x = c->x;
        p->y = c->y + 1;
        s = ajout_entete(s,p);
    }
    if (d==DROITE){
        p->x = c->x + 1;
        p->y = c->y;
        s = ajout_entete(s,p);
    }
    if (d==GAUCHE){
        p->x = c->x - 1;
        p->y = c->y;
        s = ajout_entete(s,p);
    }
}

