#ifndef SAAGE_H
#define SAAGE_H 
#include "arbres_binaires.h" 

/* cette fonction crée un fichier saage contenant la description de l’arbre A 
   Elle retourne 1 si tout s’est bien passé, 0 sinon et en cas d'echec, le fichier potentiellement créé est supprimé*/
int serialise(const char * nom_de_fichier, Arbre A);

// Fonction récursive pour la sérialisation
void serialise_rec(FILE *f, Arbre a, int niveau);

/* cette fonction lit le fichier saage dont le nom est passé en paramètre et crée l’arbre qu’il décrit dans *A.
    Elle retourne 1 si tout s’est bien passé, 0 sinon et en cas d'echec, *A est libéré
    et en cas d'echec, *A est libéré*/
int deserialise(const char * nom_de_fichier, Arbre * A);

// Fonction récursive pour la désérialisation
int deserialise_rec(FILE *f, Arbre *a, int niveau);


#endif 

