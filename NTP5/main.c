#include "TP.h"

#ifdef _WIN32
#define CLEAR() system("CLS")
#define PAUSE() system("PAUSE")
#else
#define CLEAR() printf("\n")
#define PAUSE() do { printf("Appuyer sur Entree..."); getchar(); } while (0)
#endif

#define MAX_MOT 98

int main(void)
{
	char s[MAX_MOT + 2];
	char ss[MAX_MOT + 3];
	int c, ind;

	for (;;)
	{
		ind = 0;
		printf("Donner le mot (vide pour quitter) : ");
		while ((c = getchar()) != '\n' && c != EOF)
			if (c != ' ' && ind < MAX_MOT)
				s[ind++] = (char)c;
		s[ind] = '\0';
		if (ind == 0)
			break; /* mot vide ou fin de fichier : on quitte */

		CLEAR();
		strcpy(ss, s);
		strcat(ss, "$");
		if (analyse_syntaxique(ss) == 1)
			printf("\n%s est connu\n", s);
		else
			printf("\n");
		PAUSE();
		CLEAR();
	}
	return 0;
}
