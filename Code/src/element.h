#ifndef ELEMENT_H
#define ELEMENT_H

typedef enum
{
  snake, snake_schlanga, objet, mur, vide 
} typeCase;

typedef struct element{
  typeCase type;
} *element;

element initElement(typeCase t);

#endif