#include "TP.h"

/*
 * Grammaire G' (recursivite a gauche eliminee) - cf. cahier TP5 :
 *   0 : R  -> S R'        1 : R' -> + S R'      2 : R' -> epsilon
 *   3 : S  -> T S'        4 : S' -> T S'        5 : S' -> epsilon
 *   6 : T  -> U T'        7 : T' -> * T'        8 : T' -> epsilon
 *   9 : U  -> ( R )      10 : U  -> a          11 : U  -> b
 * (numerotation du code = numerotation du cahier - 1)
 *
 * Lignes   : R, R', S, S', T, T', U
 * Colonnes : +  *  (  )  a  b  $  autre
 */
int table_analyse[7][8] = {
	{-1, -1,  0, -1,  0,  0, -1, -1},   /* R  */
	{ 1, -1, -1,  2, -1, -1,  2, -1},   /* R' */
	{-1, -1,  3, -1,  3,  3, -1, -1},   /* S  */
	{ 5, -1,  4,  5,  4,  4,  5, -1},   /* S' */
	{-1, -1,  6, -1,  6,  6, -1, -1},   /* T  */
	{ 8,  7,  8,  8,  8,  8,  8, -1},   /* T' */
	{-1, -1,  9, -1, 10, 11, -1, -1}    /* U  */
};

char derivation[maxDeri_i][maxDeri_j][8] = {
	{"S", "R'", "!"},
	{"+", "S", "R'"},
	{"epsilon", "!", "!"},
	{"T", "S'", "!"},
	{"T", "S'", "!"},
	{"epsilon", "!", "!"},
	{"U", "T'", "!"},
	{"*", "T'", "!"},
	{"epsilon", "!", "!"},
	{"(", "R", ")"},
	{"a", "!", "!"},
	{"b", "!", "!"}
};

int check_terminal(const char* c)
{
	return ((c[0] == '+') || (c[0] == '*') || (c[0] == '(') ||
		(c[0] == ')') || (c[0] == '$') || (c[0] == 'a') || (c[0] == 'b'));
}

int get_indice_mot(char c)
{
	switch (c)
	{
	case '+': return 0;
	case '*': return 1;
	case '(': return 2;
	case ')': return 3;
	case 'a': return 4;
	case 'b': return 5;
	case '$': return 6;
	default:  return 7;
	}
}

int get_indice_non_terminal(const char* nt)
{
	if (!strcmp(nt, "R"))  return 0;
	if (!strcmp(nt, "R'")) return 1;
	if (!strcmp(nt, "S"))  return 2;
	if (!strcmp(nt, "S'")) return 3;
	if (!strcmp(nt, "T"))  return 4;
	if (!strcmp(nt, "T'")) return 5;
	if (!strcmp(nt, "U"))  return 6;
	return -1;
}

int erreur(char* mot)
{
	int taille = (int)strlen(mot) - 1; /* ne pas afficher $ */
	printf("\nMot inconnu : ");
	for (int i = 0; i < taille; i++)
		printf("%c", mot[i]);
	printf("\n");
	return 0;
}

int accepter(void)
{
	return 1;
}

static void print_space(int n)
{
	for (int i = 0; i < n; i++)
		printf(" ");
}

int analyse_syntaxique(char* mot)
{
	Pile* pile = NULL;
	int ind = 0, deri, taille = (int)strlen(mot), taille_pile, resultat;
	char c[8];

	empiler(&pile, "$");
	empiler(&pile, "R");
	printf("PILE"); print_space(26);
	printf("Entree"); print_space(24);
	printf("Sortie\n\n");

	for (;;)
	{
		taille_pile = print(pile);
		print_space(30 - taille_pile);
		for (int i = ind; i < taille; i++)
			printf("%c", mot[i]);
		print_space(30 - (taille - ind));

		strcpy(c, pile->symbole);

		if (!check_terminal(c))
		{
			int col = get_indice_mot(mot[ind]);
			int lig = get_indice_non_terminal(c);
			deri = (lig >= 0) ? table_analyse[lig][col] : -1;
			if (deri == -1)
			{
				printf("ERREUR!!\n");
				resultat = erreur(mot);
				break;
			}
			printf("%s -> ", c);
			depiler(&pile);

			int n = 0; /* nombre de symboles du membre droit */
			while (n < maxDeri_j && strcmp(derivation[deri][n], "!"))
				n++;
			for (int i = 0; i < n; i++)
				printf("%s", derivation[deri][i]);
			if (strcmp(derivation[deri][0], "epsilon")) /* ne pas empiler epsilon */
				for (int i = n - 1; i >= 0; i--)
					empiler(&pile, derivation[deri][i]);
		}
		else if (c[0] == '$')
		{
			if (mot[ind] == '$' && ind == taille - 1)
			{
				printf("ACCEPTER(analyse syntaxique reussie)\n");
				resultat = accepter();
			}
			else
			{
				printf("ERREUR!!\n");
				resultat = erreur(mot);
			}
			break;
		}
		else if (c[0] == mot[ind])
		{
			depiler(&pile);
			ind++;
		}
		else
		{
			printf("ERREUR!!\n");
			resultat = erreur(mot);
			break;
		}
		printf("\n");
	}
	liberer(&pile);
	return resultat;
}
