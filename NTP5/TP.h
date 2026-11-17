#ifndef TP_H
#define TP_H

#define maxDeri_j 3
#define maxDeri_i 12
#include "Pile.h"

extern int  table_analyse[7][8];
extern char derivation[maxDeri_i][maxDeri_j][8];

int analyse_syntaxique(char*);
int check_terminal(const char*);
int get_indice_mot(char);
int get_indice_non_terminal(const char*);
int erreur(char*);
int accepter(void);

#endif
