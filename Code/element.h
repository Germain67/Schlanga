typedef enum
{
  snake, objet, mur, vide 
} typeCase;

typedef struct element{
  typeCase type;
} *element;

element initElement(typeCase t);
char caseSymbol(element elem);