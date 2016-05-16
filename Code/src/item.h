#ifndef ITEM_H
#define ITEM_H

#include "plateau.h"
#include "element.h"
#include "snake.h"

void create_item(plateau p, int nb_item);
int updateNbItem_created ();
serpent deplacement_grandir(direction d, serpent s);
serpent deplacement_reduire(direction d, serpent s);

#endif
