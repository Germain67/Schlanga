#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

/*ajout element a la tete du snake*/

snake cons(snake s, position p){
snake S;
S = malloc(sizeof(struct maillon));
S->coordonnees = p;
S->suivant= s;
return(p);
}

/*eliminer le dernier element du snake*/

snake eliminer(snake s){
    snake I = NULL;
    snake S = NULL;
    while (s->suivant != NULL){
        I = cons(I,s->coordonnees);
    }
    while (I != NULL){
        S = cons(S,I->coordonnees);
    }
return S;
}

/*deplacement*/

snake deplacement(int d, snake s){ /*2,4,6 et 8 a remplacer pas las fleches*/
s = eliminer(s);
position p;
c = s->coordonnees;
    if (d=2){
        p.x = c.x;
        p.y = c.y - 1;
        s = cons(s,p);
    }
    if (d=8){
        p.x = c.x;
        p.y = c.y + 1;
        s = cons(s,p);
    }
    if (d=6){
        p.x = c.x + 1;
        p.y = c.y;
        s = cons(s,p);
    }
    if (d=4){
        p.x = c.x - 1;
        p.y = c.y;
        s = cons(s,p);
    }
return s;
}
    
    
    
    
    
        
