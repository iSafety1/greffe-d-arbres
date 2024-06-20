#include "arbres_binaires.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* Cette fonction réserve l’espace mémoire nécessaire pour un nœud
et renvoie l’addresse mémoire où sera stocké le nœud ou NULL en cas d’echec */
Noeud* alloue_noeud(const char *s) { 
    Noeud* n = (Noeud*)malloc(sizeof(Noeud));
    if(n == NULL) {
        return NULL;
    }
    n->val = strdup(s); 
    n->fd = NULL;
    return n;
}

/* libére tout l’espace mémoire utilisé pour stocker l’arbre *A */
void liberer(Arbre *A) {
    if (*A != NULL) {
        // Vérifier si val a été alloué dynamiquement avant de le libérer
        if ((*A)->val != NULL) {
            free((*A)->val);
        }
        liberer(&(*A)->fg);
        liberer(&(*A)->fd);
        free(*A);
        *A = NULL;
    }
}

/* cette fonction crée l'arbre A1 et renvoie l'arbre A1 */
Arbre cree_A_1(void) {
    Noeud *arbre = alloue_noeud("arbre");
    Noeud *binaire = alloue_noeud("binaire");
    Noeud *ternaire = alloue_noeud("ternaire");

    if(arbre == NULL || binaire == NULL || ternaire == NULL) {
        return NULL;
    }
    arbre->fg = binaire;
    arbre->fd = ternaire;

    return arbre;
}

/* cette fonction crée l'arbre A2 et renvoie l'arbre A2 */
Arbre cree_A_2(void) {
    Noeud *anemone = alloue_noeud("Anémone");
    Noeud *camomille1 = alloue_noeud("Camomille");
    Noeud *camomille2 = alloue_noeud("Camomille");
    Noeud *camomille3 = alloue_noeud("Camomille");
    Noeud *dahlia = alloue_noeud("Dahlia");
    Noeud *iris = alloue_noeud("Iris");
    Noeud *jasmin = alloue_noeud("Jasmin");
    
    if (anemone == NULL || camomille1 == NULL || camomille2 == NULL || dahlia == NULL || iris == NULL || jasmin == NULL) {
        return NULL;
    }    
    anemone->fg = camomille1;
    anemone->fd = camomille2;
    camomille2->fg = dahlia;
    dahlia->fd = camomille3;
    camomille3->fg = iris;
    camomille3->fd = jasmin;

    return anemone;
}

/* cette fonction crée l'arbre A3 et renvoie l'arbre A3 */
Arbre cree_A_3(void) {
    Noeud *intel_i9 = alloue_noeud("Intel Core i9");
    Noeud *apple_m3_max = alloue_noeud("Apple M3 Max");
    Noeud *amd_ryzen_9 = alloue_noeud("AMD Ryzen 9");
    Noeud *intel_i9_2 = alloue_noeud("Intel Core i9");
    Noeud *intel_i9_3 = alloue_noeud("Intel Core i9");
    Noeud *intel_i9_4 = alloue_noeud("Intel Core i9");

    if(intel_i9 == NULL || apple_m3_max == NULL || amd_ryzen_9 == NULL || intel_i9_2 == NULL || intel_i9_3 == NULL || intel_i9_4 == NULL) {
        return NULL;
    }
    intel_i9->fg = apple_m3_max;
    intel_i9->fd = intel_i9_2;
    apple_m3_max->fd = amd_ryzen_9;
    intel_i9_2->fg = intel_i9_3;
    amd_ryzen_9->fg = intel_i9_4;

    return intel_i9;
}

/* cette fonction crée l'arbre B c'est à dire l'abre à greffer sur A_1 et renvoie l'arbre B  */
Arbre cree_B(void) {
    Noeud *binaire = alloue_noeud("binaire");
    Noeud *lexicographique = alloue_noeud("lexicographique");
    Noeud *aire = alloue_noeud("n-aire");

    if(binaire == NULL || lexicographique == NULL || aire == NULL) {
        return NULL;
    }
    binaire->fg = lexicographique;
    binaire->fd = aire;

    return binaire;
}

/* cette fonction crée l'arbre C c'est à dire l'abre à greffer sur A_2 et renvoie l'arbre C  */
Arbre cree_C(void) {
    Noeud *camomille = alloue_noeud("Camomille");
    Noeud *lilas = alloue_noeud("Lilas");
    Noeud *rose = alloue_noeud("Rose");

    if(camomille == NULL || lilas == NULL || rose == NULL) {
        return NULL;
    }
    camomille->fg = lilas;
    camomille->fd = rose;

    return camomille;
}

/* cette fonction crée l'arbre D c'est à dire l'abre à greffer sur A_3 et renvoie l'arbre D  */
Arbre cree_D(void) {
    Noeud *intel_i9 = alloue_noeud("Intel Core i9");
    Noeud *apple_m3_max = alloue_noeud("Apple M3 Max");
    Noeud *amd_ryzen_9 = alloue_noeud("AMD Ryzen 9");
    Noeud *intel_i9_2 = alloue_noeud("Intel Core i9");

    if(intel_i9 == NULL || apple_m3_max == NULL || amd_ryzen_9 == NULL || intel_i9_2 == NULL) {
        return NULL;
    }
    intel_i9->fg = intel_i9_2; 
    intel_i9_2->fg = apple_m3_max;
    intel_i9_2->fd = amd_ryzen_9;

    return intel_i9;
}

/* écrit les trois premières lignes de déclaration du fichier f */
void ecrireDebut(FILE *f) {
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "node [ shape = record , height = .1 ]\n");
    fprintf(f, "edge [ tailclip = false , arrowtail = dot , dir = both ];\n");
}

/* écrit la description de l'arbre a dans le fichier f */
void ecrireArbre(FILE *f, Noeud *a) { 
    if (a != NULL) {
        fprintf(f, "n%p [label=\"<gauche> | <valeur> %s | <droit>\"];\n", a, a->val);
        if (a->fg != NULL) {
            fprintf(f, "n%p:gauche:c -> n%p:valeur;\n", a, a->fg);
            ecrireArbre(f, a->fg);
        }
        if (a->fd != NULL) {
            fprintf(f, "n%p:droit:c -> n%p:valeur;\n", a, a->fd);
            ecrireArbre(f, a->fd);
        }
    }
}

/* écrit la dernière ligne du fichier f */
void ecrireFin(FILE *f) { 
    fprintf(f, "}\n");
}

/* dessine l'arbre a dans le fichier f */
void dessine(FILE *f, Noeud *a) {
    ecrireDebut(f);
    ecrireArbre(f, a);
    ecrireFin(f);
}


// Fonction pour construire un arbre binaire
int construit_arbre(Arbre *a) {
    char buffer[256];
    int type;

    // Lire le type du nœud (0 pour NULL, 1 pour un nœud non vide)
    if (scanf("%d", &type) != 1) {
        fprintf(stderr, "Erreur lors de l'extraction du type du nœud.\n");
        return 0; 
    }

    // Si le type est 0, le nœud est vide
    if (type == 0) {
        *a = NULL;
        return 1; 
    }

    // Alloue de la mémoire pour un nouveau nœud
    *a = (Noeud *)malloc(sizeof(Noeud));
    if (*a == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour le nœud.\n");
        return 0;
    } 

    // Lire le reste de la ligne
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Erreur lors de la lecture de la séquence.\n");
        free(*a);
        return 0; 
    }

    // Allouer de la mémoire pour la valeur
    (*a)->val = strdup(buffer);
    if ((*a)->val == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour la valeur du nœud.\n");
        free(*a); 
        return 0; 
    }

    // Supprimer le saut de ligne à la fin de la valeur
    (*a)->val[strcspn((*a)->val, "\n")] = '\0';

    // Initialise les sous-arbres à NULL
    (*a)->fg = NULL;
    (*a)->fd = NULL;

    // Construit récursivement les sous-arbres gauche et droit
    if (!construit_arbre(&(*a)->fg) || !construit_arbre(&(*a)->fd)) {
        fprintf(stderr, "Erreur lors de la construction des sous-arbres.\n");
        free((*a)->val);
        free(*a);      
        return 0;       
    }

    return 1; 
}

/*
int main (){
    Arbre a = NULL;
    printf("Entrez un arbre binaire et 0 pour arrêter : \n");
    construit_arbre(&a);
    FILE *f = fopen("arbre.dot", "w");
    if (f == NULL){
        printf("Erreur à l'ouverture du fichier nom.dot");
    }
    else{
        dessine(f, a);
    }
    fclose(f);
    system("dot -Tpdf arbre.dot -o arbre.pdf");
    system("evince arbre.pdf &");
    liberer(&a);

    
    return 0;
}
*/


