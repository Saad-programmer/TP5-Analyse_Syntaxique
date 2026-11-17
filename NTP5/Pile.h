#ifndef PILE_H
#define PILE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_SYMBOLE 8

typedef struct pile
{
	char* symbole;
	struct pile* svt;
} Pile;

int   empty(Pile*);
void  empiler(Pile**, const char*);
Pile* allocate(const char*);
void  depiler(Pile**);
void  liberer(Pile**);
int   print(Pile*);

#endif
