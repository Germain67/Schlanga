#ifndef ELEMENT_H
#define ELEMENT_H

typedef enum
{
  snake, objet, mur, vide 
} typeCase;

typedef struct element{
  typeCase type;
} *element;

element initElement(typeCase t);
char caseSymbol(element elem);
/*typeCase etat_case(plateau p, position pos);*/

#endif