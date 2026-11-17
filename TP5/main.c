#include "TP.h"
#include <stdlib.h>


int main()
{
	char s[100];
	char ss[100];
	char c;
	int ind = 0;
	do
	{
		ind = 0;
		printf("Donner le mot : ");
		while ((c = getchar()) != '\n')
			if (c != ' ')
				s[ind++] = c;
		s[ind] = '\0';
		system("CLS");
		strcpy(ss, s);
		strcat(ss, "$");
		analyse_syntaxique(ss) == 1 ? printf("\n%s est connu\n", s) : printf("\n");
		system("PAUSE");
		system("CLS");
	} while (1);
	return 1;
}

