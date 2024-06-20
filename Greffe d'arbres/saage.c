#include "saage.h" 
  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fonction recursive pour la sérialisation */
void serialise_rec(FILE *f, Arbre a, int niveau) {
    // Ecrire le nombre d'espaces correspondant au niveau de l'arbre
    for (int i = 0; i < niveau; i++) {
        fprintf(f, "    ");
    }

    // Si le nœud est NULL, écrire "NULL"
    if (a == NULL) {
        fprintf(f, "NULL\n"); 
    } else {
        fprintf(f, "Valeur : %s\n", a->val); // Ecrire la valeur du nœud

        if (a->fg != NULL){
            fprintf(f, "%*sGauche : \n", niveau * 4, "");  // Ecrire "Gauche : " et appeler la fonction récursive pour le sous-arbre gauche
            serialise_rec(f, a->fg, niveau + 1);
        }
        else{
            fprintf(f, "%*sGauche : NULL\n", niveau * 4, ""); 
        }
        if (a->fd != NULL)
        {
            fprintf(f, "%*sDroite : \n", niveau * 4, "");
            serialise_rec(f, a->fd, niveau + 1);
        } else {
            fprintf(f, "%*sDroite : NULL\n", niveau * 4, "");
        }

    }
}

/* fonction creant un fichier saage contenant la description de l’arbre A 
    Elle retourne 1 si tout s’est bien passé, 0 sinon et en cas d'echec, le fichier potentiellement créé est supprimé*/
int serialise(const char *nom_de_fichier, Arbre a) {
    // Ouvrir le fichier en écriture
    FILE *f = fopen(nom_de_fichier, "w");
    // vérifier si le fichier est bien ouvert 
    if (f == NULL) {
        return 0;
    }
    
    // Appeler la fonction récursive pour la sérialisation
    serialise_rec(f, a, 0);

    // Fermer le fichier et vérifier si la fermeture s'est bien passée
    if (fclose(f) != 0) {
        remove(nom_de_fichier);
        return 0;
    }

    return 1;
}


/* fonction recursive pour la désérialisation */
int deserialise_rec(FILE *f, Arbre *a, int niveau) {
    char buffer[256];
    char valeur[256];

    // Lire une ligne entière
    if (fgets(buffer, sizeof(buffer), f) == NULL) {
        fprintf(stderr, "Erreur lors de la lecture du fichier de sauvegarde\n");
        return 0;
    }

    // Analyser la valeur du nœud
    if (sscanf(buffer, " Valeur : %[^\n]", valeur) != 1 || strlen(valeur) >= 256) {
        fprintf(stderr, "Erreur lors de l'analyse de la valeur du nœud\n");
        return 0;
    }

    // Allouer de la mémoire pour le nœud
    *a = (Noeud*)malloc(sizeof(Noeud));
    if (*a == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        return 0;
    }

    // Allouer de la mémoire pour la valeur
    (*a)->val = strdup(valeur);
    if ((*a)->val == NULL) {
        free(*a);
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        return 0;
    }

    // Lire les sous-arbres gauche et droit
    if (fgets(buffer, sizeof(buffer), f) == NULL || strstr(buffer, "Gauche : ") == NULL) {
        free((*a)->val);
        free(*a);
        fprintf(stderr, "Erreur lors de la désérialisation du sous-arbre gauche\n");
        return 0;
    }

    if (strstr(buffer, "NULL") != NULL) {
        (*a)->fg = NULL;
    } else if (!deserialise_rec(f, &(*a)->fg, niveau + 1)) {
        liberer(a);
        fprintf(stderr, "Erreur lors de la désérialisation du sous-arbre gauche\n");
        return 0;
    }

    if (fgets(buffer, sizeof(buffer), f) == NULL || strstr(buffer, "Droite : ") == NULL) {
        free((*a)->val);
        free(*a);
        fprintf(stderr, "Erreur lors de la désérialisation du sous-arbre droit\n");
        return 0;
    }

    if (strstr(buffer, "NULL") != NULL) {
        (*a)->fd = NULL;
    } else if (!deserialise_rec(f, &(*a)->fd, niveau + 1)) {
        liberer(a);
        fprintf(stderr, "Erreur lors de la désérialisation du sous-arbre droit\n");
        return 0;
    }

    return 1;
}

/* fonction lisant le fichier saage dont le nom est passé en paramètre et créant l’arbre qu’il décrit dans *A.
    Elle retourne 1 si tout s’est bien passé, 0 sinon et en cas d'echec, *A est libéré*/
int deserialise(const char *nom_de_fichier, Arbre *a) {
    // Ouvrir le fichier en lecture
    FILE *f = fopen(nom_de_fichier, "r"); 

    // Vérifier si le fichier est bien ouvert
    if (f == NULL) {
        return 0;
    }

    // Appeler la fonction récursive pour la désérialisation
    int result = deserialise_rec(f, a, 0);

    // Fermer le fichier et vérifier si la fermeture s'est bien passée
    if (fclose(f) != 0 || result==0) {
        liberer(a); 
        return 0;
    }

    return result;
}

/*
int main (){
    Arbre a = NULL;
    deserialise("Fichiers_saage_de_tests/A_2.saage", &a);
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

