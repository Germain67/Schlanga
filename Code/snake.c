#include "snake.h"
#include <stdio.h>
#include <stdlib.h>



position cree_position(int x, int y) {
    position p = NULL;
    p = (position) malloc(sizeof(position));
    p->x = x;
    p->y = y;
    return p;
}



/*ajout element a la tete du snake*/

serpent ajout_entete(serpent s, position p){
    serpent s = (serpent) malloc(sizeof(struct serpent));
    s->coordonnees = pos;
    s->suivant = suivant;
    return s;
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

//Creation du serpent pos= position de la queue
serpent init_serpent(int taille, position pos, direction dir)  {
    int i;
    serpent s = (serpent) malloc(sizeof(struct serpent));
    position pos=cree_position(25,25);
    ajout_entete(s, pos);
    position tmp=pos;
    for (i=0; i<taille; i++) {
        if (dir==BAS) {
            tmp->y-=1;
            ajout_entete(s, tmp);
        }
        if (dir==HAUT) {
            tmp->y+=1;
            ajout_entete(s, tmp);
        }

        if (dir==DROITE) {
            tmp->x+=1;
            ajout_entete(s, tmp);
        }

        if (dir==GAUCHE) {
            tmp->x-=1;
            ajout_entete(s, tmp);
        }

    }
    return s;
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

