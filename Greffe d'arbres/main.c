#include "arbres_binaires.c"
#include "greffe.c"
#include "saage.c"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction principale

int main(int argc, char *argv[]) {
    // Vérifier le nombre d'arguments
    if (argc < 2) {
        printf("Usage: %s -E fichier.saage | -G source.saage greffon.saage\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-E") == 0 && argc == 3) {
        // Option -E: Crée une sauvegarde dans le fichier .saage d'un arbre saisi par l'utilisateur
        Arbre A;
        if (construit_arbre(&A)) {
            int success = serialise(argv[2], A);
            if (success) {
                printf("Sauvegarde réussie dans %s\n", argv[2]);
            } else {
                printf("Erreur lors de la sauvegarde dans %s\n", argv[2]);
            }
                    FILE *f = fopen("arbre.dot", "w");
            if (f == NULL){
                printf("Erreur à l'ouverture du fichier nom.dot");
            }
            else{
                dessine(f, A);
            }
            fclose(f);
            system("dot -Tpdf arbre.dot -o arbre.pdf");
            system("evince arbre.pdf &");
            liberer(&A);
        } else {
            printf("Erreur lors de la construction de l'arbre\n");
            return EXIT_FAILURE;
        }

    } else if (strcmp(argv[1], "-G") == 0 && argc == 4) {

        // Option -G: Crée l'arbre avec le greffon appliqué à l'arbre source
        Arbre source, greffon, resultat;

        // Chargement de l'arbre source
        if (!deserialise(argv[2], &source)) {
            printf("Erreur lors du chargement de l'arbre source depuis %s\n", argv[2]);
            return EXIT_FAILURE;
        }

        // Chargement du greffon
        if (!deserialise(argv[3], &greffon)) {
            printf("Erreur lors du chargement du greffon depuis %s\n", argv[3]);
            liberer(&source);
            return EXIT_FAILURE;
        }

        // Application de la greffe
        resultat = expansion(&source, greffon);

        FILE *f = fopen("arbre.dot", "w");
        if (f == NULL){
            printf("Erreur à l'ouverture du fichier nom.dot");
        }
        else{
            dessine(f, resultat);
        }
        fclose(f);
        system("dot -Tpdf arbre.dot -o arbre.pdf");
        system("evince arbre.pdf &");

        FILE *temp_stdout = freopen("temp_stdout.saage", "w", stdout);
        if (temp_stdout == NULL) {
            perror("Erreur lors de la redirection de stdout vers un fichier temporaire");
            return EXIT_FAILURE;
        }

        // Appel de la fonction serialise
        if (serialise("temp_stdout.saage", resultat)) {
                fclose(temp_stdout);

                // Restaurer stdout
                freopen("/dev/tty", "w", stdout);


                // Afficher le contenu du fichier temporaire en utilisant "cat"
                char cat_command[100];
                snprintf(cat_command, sizeof(cat_command), "cat temp_stdout.saage");
                system(cat_command);
                
        } else {
            fprintf(stderr, "Erreur lors de la sérialisation de l'arbre résultant\n");
        }




        // Libération de la mémoire
        //liberer(&source);
        liberer(&greffon);
        liberer(&resultat);
    } else {
        printf("Usage: %s -E fichier.saage | -G source.saage greffon.saage\n", argv[0]);
        return EXIT_FAILURE;
    }
}

