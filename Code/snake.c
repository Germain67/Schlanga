#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

serpent init_serpent() {
	serpent s = NULL;
	s = malloc(sizeof(struct serpent));
	return s;
}

/*void free_serpent(serpent s) {

}*/

/*ajout element a la tete du snake*/

void ajout_entete(serpent s, position p){
	s->suivant = s;
	s->coordonnees = p;
}

/*eliminer le dernier element du snake*/

void suppression_queue(serpent s){
    serpent I = init_serpent();
    serpent S = init_serpent();
    while (s->suivant != NULL){
        ajout_entete(I,s->coordonnees);
	s=s->suivant;
    }
    while (I != NULL){
        ajout_entete(S,I->coordonnees);
	I=I->suivant;
    }
    s->suivant=S->suivant;
    s->coordonnees=S->coordonnees;
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
        ajout_entete(s,p);
    }
    if (d==HAUT){
        p->x = c->x;
        p->y = c->y + 1;
        ajout_entete(s,p);
    }
    if (d==DROITE){
        p->x = c->x + 1;
        p->y = c->y;
        ajout_entete(s,p);
    }
    if (d==GAUCHE){
        p->x = c->x - 1;
        p->y = c->y;
        ajout_entete(s,p);
    }
}

