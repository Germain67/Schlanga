/**
 * \struct element.h
*/

#ifndef ELEMENT_H
#define ELEMENT_H

/*
 * \enum typeCase
 * \brief énumération des différents éléments possibles
 *
 */
typedef enum
{
  snake, snake_schlanga, mur, vide, grandir, reduire, accelerer, ralentir
} typeCase;

typedef struct element{
  typeCase type;
} *element;

element initElement(typeCase t);
void updateElement(typeCase t, element e);

#endif
