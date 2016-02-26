plateau initPlateau(int hauteur, int largeur);
void showPlateau(plateau p);

/* Plateau */
typedef struct plateau{
	element** data;
	int hauteur;
	int largeur;
} *plateau;