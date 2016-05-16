#ifndef ELEMENT_H
#define ELEMENT_H

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
