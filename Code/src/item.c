#include "item.h"
#include <stdlib.h>
#include <time.h>

// Fonction create_item pas encore testée.
plateau create_item(plateau p, int hauteur, int largeur) {
	int x,y;
	int b=0;	
	while (p->data[x][y]->type != vide && b!=1){
		srand(time(null));
		x=(Rand() % largeur)+1;

		srand(time(null));
		y=(Rand() % hauteur)+1;
		
		b=1;
	}
	
	p->date[x][y]->type = item;
	return p;
}
