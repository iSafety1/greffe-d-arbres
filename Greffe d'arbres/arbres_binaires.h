#ifndef ARBRES_BINAIRES_H
#define ARBRES_BINAIRES_H

#include <stdio.h>

/*  la structure permettant de manipuler les arbres */
typedef struct _noeud {
    char * val;
    struct _noeud *fg, *fd;
} Noeud, *Arbre;


/* Cette fonction réserve l’espace mémoire nécessaire pour un nœud
et renvoie l’addresse mémoire où sera stocké le nœud ou NULL en cas d’echec */
Noeud * alloue_noeud(const char * s);

/* libére tout l’espace mémoire utilisé pour stocker l’arbre *A */
void liberer(Arbre * A);
 
/* cette fonction crée l'arbre A1 et renvoie l'arbre A1 */
Arbre cree_A_1(void);

/* cette fonction crée l'arbre A2 et renvoie l'arbre A2 */
Arbre cree_A_2(void);

/* cette fonction crée l'arbre A3 et renvoie l'arbre A3 */
Arbre cree_A_3(void);

/* cette fonction crée l'arbre B c'est à dire l'abre à greffer sur A_1 et renvoie l'arbre B  */
Arbre cree_B(void);

/* cette fonction crée l'arbre C c'est à dire l'abre à greffer sur A_2 et renvoie l'arbre C  */
Arbre cree_C(void);

/* cette fonction crée l'arbre D c'est à dire l'abre à greffer sur A_3 et renvoie l'arbre D  */
Arbre cree_D(void);

/* cette fonction  permet à l’utilisateur de saisir le parcours profondeur infixe d’un arbre et de créer et stocker
celui-ci dans *A. Elle renvoie 1 en cas de succès et 0 en cas d’échec */
int construit_arbre(Arbre *a);

/* écrit les trois premières lignes de déclaration du fichier f */
void ecrireDebut(FILE *f);

/* écrit la description de l'arbre a dans le fichier f */
void ecrireArbre(FILE *f, Noeud *a);

/* écrit la dernière ligne du fichier f */
void ecrireFin(FILE *f);

/* dessine l'arbre a dans le fichier f */
void dessine(FILE *f, Noeud *a);

#endif
