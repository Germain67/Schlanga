#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

serpent init_serpent() {
	serpent s = NULL;
	s = (serpent) malloc(sizeof(struct serpent));
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
    serpent tete = init_serpent();
	tete->suivant = s;
	tete->coordonnees = p;
    return tete;
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

serpent Free_serpent(serpent s) {
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
    suppression_queue(s);
    position p;
    position c;
    c = s->coordonnees;
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

