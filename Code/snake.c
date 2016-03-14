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

serpent ajout_entete(serpent suivant, position pos){
    serpent s = (serpent) malloc(sizeof(struct serpent));
    s->coordonnees = pos;
    s->suivant = suivant;
    return s;
}

position get_position_queue(serpent s){
    serpent courant = s;
    while (courant->suivant !=NULL) {
       courant = courant->suivant;
    }
    return courant->coordonnees;
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

void free_position(position pos) {
    free(pos);
}

//Creation du serpent pos= position de la queue
serpent init_serpent(int taille, position pos, direction dir)  {
    serpent s = NULL;
    int i;
    position p = pos;
    position p1;
    s = ajout_entete(s,pos);
    if (dir == HAUT){
        for (i=0;i<taille;i++){
            p1 = cree_position(pos->x,pos->y + i);
            s = ajout_entete(s,p1);
        }
   }
   if (dir == BAS){
        for (i=0;i<taille;i++){
            p1 = cree_position(pos->x,pos->y - i);
            s = ajout_entete(s,p1);
        }
   }
   if (dir == DROITE){
        for (i=0;i<taille;i++){
            p1 = cree_position(pos->x + i,pos->y);
            s = ajout_entete(s,p1);
        }
   }
   if (dir == GAUCHE){
        for (i=0;i<taille;i++){
            p1 = cree_position(pos->x - i,pos->y);
            s = ajout_entete(s,p1);
        }
   }
   return s;
}


/*deplacement*/

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



