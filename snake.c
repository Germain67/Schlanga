#include "snake.h"
#include <stdio.h>
#include <stdlib.h>


/*ajout element a la tete du snake*/

serpent cons(serpent s, position p){
    serpent S;
    S = malloc(sizeof(struct serpent));
    S->coordonnees = p;
    S->suivant= s;
return(s);
}

/*eliminer le dernier element du snake*/

serpent eliminer(serpent s){
    serpent I = NULL;
    serpent S = NULL;
    while (s->suivant != NULL){
        I = cons(I,s->coordonnees);
    }
    while (I != NULL){
        S = cons(S,I->coordonnees);
    }
return S;
}

/*deplacement*/

serpent deplacement(int d, serpent s){ /*2,4,6 et 8 a remplacer pas las fleches*/
s = eliminer(s);
position p;
position c;
c = s->coordonnees;
    if (d==2){
        p->x = c->x;
        p->y = c->y - 1;
        s = cons(s,p);
    }
    if (d==8){
        p->x = c->x;
        p->y = c->y + 1;
        s = cons(s,p);
    }
    if (d==6){
        p->x = c->x + 1;
        p->y = c->y;
        s = cons(s,p);
    }
    if (d==4){
        p->x = c->x - 1;
        p->y = c->y;
        s = cons(s,p);
    }
return s;
}

