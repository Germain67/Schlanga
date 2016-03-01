#include "snake.h"
#include <stdio.h>
#include <stdlib.h>


/*ajout element a la tete du snake*/

void ajout_entete(serpent s, position p){
    serpent S;
    S = malloc(sizeof(struct serpent));
    S->coordonnees = p;
    S->suivant= s;
return(S);
}

/*eliminer le dernier element du snake*/

void suppression_queue(serpent s){
    serpent I = NULL;
    serpent S = NULL;
    while (s->suivant != NULL){
        I = ajout_entete(I,s->coordonnees);
    }
    while (I != NULL){
        S = ajout_entete(S,I->coordonnees);
    }
return S;
}

/*deplacement*/

void deplacement(direction d, serpent s){
    s = eliminer(s);
    position p;
    position c;
    c = s->coordonnees;
    if (d==BAS){
        p->x = c->x;
        p->y = c->y - 1;
        s = cons(s,p);
    }
    if (d==HAUT){
        p->x = c->x;
        p->y = c->y + 1;
        s = cons(s,p);
    }
    if (d==DROITE){
        p->x = c->x + 1;
        p->y = c->y;
        s = cons(s,p);
    }
    if (d==GAUCHE){
        p->x = c->x - 1;
        p->y = c->y;
        s = cons(s,p);
    }
}

