#include "element.h"
#include "snake.h"
#include "plateau.h"

/**
 * \fn           initElement
 * \brief       alloue la mémoire nécessaire et initialise un element dont le type est donné en argument
 * \param      t type de l'élément à générer
 * \return     element du type donné en argument
 */


element initElement(typeCase t){
	element e = (element) malloc(sizeof(element));
	e->type = t;
	return e;
}

/**
 * \fn         updateElement
 * \brief      Modifie le type d'un element
 * \param      e element où le type est à modifier et t type de l'élément à modifier
 * \return     rien
 */
void updateElement(typeCase t, element e){
	e->type = t;
}
