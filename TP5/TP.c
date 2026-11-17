#include "TP.h"
#include <string.h>

int table_analyse[7][8] = { {-1, -1, 0, -1, 0, 0, -1, -1},
							{1, -1, -1, 2, -1, -1, 2, -1},
							{-1, -1, 3, -1, 3, 3, -1, -1},
							{5, -1, 4, 5, 4, 4, 5, -1},
							{-1, -1, 6, -1, 6, 6, -1, -1},
							{8, 7, 8, 8, 8, 8, 8, -1},
							{-1, -1, 9, -1, 10, 11, -1, -1} };

char derivation[maxDeri_i][maxDeri_j][8] = { {"S","R'", "!"},
									   	   {"+", "S","R'"},
										   {"epsilon", "!","!"}, 
										   {"T", "S'","!"}, 
										   {"T", "S'","!"}, 
										   {"epsilon", "!","!"},
										   {"U", "T'","!"}, 
										   {"*", "T'","!"},
										   {"epsilon", "!","!"},
										   {"(", "R",")"},
										   {"a", "!","!"},
										   {"b", "!","!"}, };




int check_terminal(char c[8])
{
	return ((c[0] == '+') || (c[0] == '*') || (c[0] == '(') || 
		(c[0] == ')') || (c[0] == '$') || (c[0] == 'a') || (c[0] == 'b'));
}

int get_indice_mot(char c)
{
	switch (c)
	{
	case '+':
		return 0;
	case '*':
		return 1;
	case '(':
		return 2;
	case ')':
		return 3;
	case 'a':
		return 4;
	case 'b':
		return 5;
	case '$':
		return 6;
	default:
		return 7;
	}
}

int get_indice_non_terminal(char non_terminal[8])
{
	if (!strcmp(non_terminal, "R"))
		return 0;
	if (!strcmp(non_terminal, "R'"))
		return 1;
	if (!strcmp(non_terminal, "S"))
		return 2;
	if (!strcmp(non_terminal, "S'"))
		return 3;
	if (!strcmp(non_terminal, "T"))
		return 4;
	if (!strcmp(non_terminal, "T'"))
		return 5;
	if (!strcmp(non_terminal, "U"))
		return 6;
	return -1;
}

int erreur(char* mot)
{
	//Pour ne pas afficher $
	int taille = strlen(mot) - 1;
	printf("\nMot inconnu : ");
	for (int i = 0; i < taille; i++)
		printf("%c", mot[i]);
	printf("\n");
	return 0;
}

int accepter()
{
	return 1;
}

void print_space(int n)
{
	for (int i = 0; i < n; i++)
		printf(" ");
}

int analyse_syntaxique(char* mot)
{
	Pile* pile = 0;
	int ind = 0, deri, taille = strlen(mot), taille_pile;
	char c[8];
	empiler(&pile, "$");
	empiler(&pile, "R");
	printf("PILE"); print_space(26);
	printf("Entree"); print_space(24); 
	printf("Sortie\n\n");
	do
	{
		taille_pile = print(&pile);
		print_space(30 - taille_pile);
		for (int i = ind; i < taille; i++)
			printf("%c", mot[i]);
		print_space(30 - (taille - ind));
		strcpy(c, pile->symbole);
		if (!check_terminal(c))
		{
			if ((deri = table_analyse[get_indice_non_terminal(c)][get_indice_mot(mot[ind])]) != -1)
			{
				printf("%s -> ", pile->symbole);
				depiler(&pile);
				int max = maxDeri_j - 1;
				while ((!strcmp(derivation[deri][max], "!")) && max) max--;
				for (int i = 0; i <= max; i++)
				{
					if (strcmp(derivation[deri][max], "epsilon")) // ne pas empiler epsilon
						empiler(&pile, derivation[deri][max - i]);
					printf("%s", derivation[deri][i]);
				}
			}
			else
			{
				printf("ERREUR!!\n");
				return erreur(mot);
			}
		}
		else
		{
			if (c[0] == '$')
			{
				if (mot[ind] == '$')
				{
					printf("ACCEPTER(analyse syntaxique reussie)\n");
					return accepter();
				}
				else
				{
					printf("ERREUR!!\n");
					return erreur(mot);
				}
			}
			else
			{
				if (c[0] == mot[ind])
				{
					depiler(&pile);
					ind++;
				}
				else
				{
					printf("ERREUR!!\n");
					return erreur(mot);
				}
			}
		}
		printf("\n");
	} while (1);
	return 1;
}