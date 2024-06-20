#include "greffe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour copier un arbre
int copie(Arbre *dest, Arbre source) {
    if(source == NULL) {
        *dest = NULL;
        return 1;
    }
    *dest = alloue_noeud(source->val);
    if(*dest == NULL) {
        return 0;
    }
    if(!copie(&(*dest)->fg, source->fg) || !copie(&(*dest)->fd, source->fd)) {
        liberer(dest);
        return 0;
    }
    return 1;
}

// Fonction pour greffer les fils
void greffer_fils(Arbre *n, Arbre *fg, Arbre *fd) {
   if (*n == NULL) return;

    // Parcourir l'arbre dans l'ordre suffixe
    greffer_fils(&(*n)->fg, fg, fd);
    greffer_fils(&(*n)->fd, fg, fd);

    // Si le nœud n'a pas de fils gauche, greffer le sous-arbre gauche
    if ((*n)->fg == NULL) {
        copie(&(*n)->fg, *fg);
    }

    // Si le nœud n'a pas de fils droit, greffer le sous-arbre droit
    if ((*n)->fd == NULL) {
        copie(&(*n)->fd, *fd);
    }
} 

// Fonction pour effectuer la greffe
Arbre greffer(Arbre *n, Arbre *B) {
    if (*n == NULL) return NULL;

    // Parcourir l'arbre dans l'ordre suffixe
    greffer(&(*n)->fg, B);
    greffer(&(*n)->fd, B);

    // Si la valeur du nœud est la même que celle de la racine de B
    if (strcmp((*n)->val, (*B)->val) == 0) {
        Arbre copie_B;
        // Faire une copie de B
        copie(&copie_B, *B);
        // Greffer les sous-arbres de n sur la copie de B
        greffer_fils(&copie_B, &(*n)->fg, &(*n)->fd);
        // Remplacer n par la copie de B
        liberer(n);
        *n = copie_B;
    }
    return *n; 
}

// Fonction principale pour effectuer la greffe
Arbre expansion(Arbre *A, Arbre B) {
    if (*A == NULL || B == NULL) 
        return NULL; // Échec si l'un des arbres est vide

    return greffer(A, &B); 
}  

/*
int main(void) {
    //Arbre A1 = cree_A_1();    
    //Arbre A2 = cree_A_2();
    Arbre A3 = cree_A_3();
    //Arbre B = cree_B();
    //Arbre C = cree_D();
    Arbre D = cree_D();

    FILE *f = fopen("arbre.dot", "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
    {
        expansion(&A3, D);
        dessine(f, A3);      
    }
    fclose(f);
    system("dot -Tpdf arbre.dot -o arbre.pdf");
    system("evince arbre.pdf &");
    
    return 0;
}

*/