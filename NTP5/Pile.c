#include "Pile.h"

int empty(Pile* maPile)
{
	return (maPile == NULL);
}

Pile* allocate(const char* _symbole)
{
	Pile* NE = (Pile*)malloc(sizeof(Pile));
	if (!NE)
		exit(EXIT_FAILURE);
	NE->symbole = (char*)malloc(TAILLE_SYMBOLE);
	if (!NE->symbole)
		exit(EXIT_FAILURE);
	strncpy(NE->symbole, _symbole, TAILLE_SYMBOLE - 1);
	NE->symbole[TAILLE_SYMBOLE - 1] = '\0';
	NE->svt = NULL;
	return NE;
}

void empiler(Pile** maPile, const char* _symbole)
{
	Pile* NE = allocate(_symbole);
	NE->svt = *maPile;
	*maPile = NE;
}

void depiler(Pile** maPile)
{
	Pile* tmp;
	if (!empty(*maPile))
	{
		tmp = *maPile;
		*maPile = tmp->svt;
		free(tmp->symbole);
		free(tmp);
	}
}

void liberer(Pile** maPile)
{
	while (!empty(*maPile))
		depiler(maPile);
}

/* Affiche la pile du fond (gauche) vers le sommet (droite), sans la modifier.
   Retourne le nombre de caracteres affiches. */
int print(Pile* pile)
{
	int taille;
	if (empty(pile))
		return 0;
	taille = print(pile->svt);
	printf("%s", pile->symbole);
	return taille + (int)strlen(pile->symbole);
}
