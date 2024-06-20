#ifndef GREFFE_H
#define GREFFE_H
#include "arbres_binaires.h"

/* cette fonction copie l'arbre source dans l'arbre dest et renvoie 1 en cas de succès et 0 en cas d'échec */
int copie(Arbre *dest, Arbre source);

/* cette fonction modifie l’arbre *A de sorte qu’après l’appel de fonctions, celui-c contienne la greffe de l’arbre B sur A. 
   La fonction renvoie 1 en cas de succès et 0 en cas d’échec */
Arbre  expansion(Arbre *A, Arbre B);

/* ctte fonction greffe les fils fg et fd sur le nœud n */
void greffer_fils(Arbre *n, Arbre *fg, Arbre *fd);

/* cette fonction effectue la greffe de l'arbre B sur l'arbre n */
Arbre greffer(Arbre *n, Arbre *B);

#endif 
