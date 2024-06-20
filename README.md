# greffe-d-arbres

Descriptif du Projet 
Le projet a pour objectif d’implémenté une greffe génétiquement modifié d’arbres binaires ; en mettant aussi en place un système de visualisation de l’arbre et de sérialisation.
    • Les fonctions implémentées 
    • Les difficultés rencontrées 
    • La répartition du travail 
Les fonctions 
	Nous avons divisé le projet en 3 modules et le main.
    • Arbres_binaires
    • Greffe
    • Saage
    • main

Dans le module Arbres_binaires nous avons mis en place les fonctions de creation d’un nœud qui alloue l’espace nécessaire pour l’allocation d’un nœud. Mais aussi la libération d’un arbre « void libérer (Arbre *A) » cette fonction s’appelle récursivement pour libérer tout l’arbre.
Mais aussi quatre fonctions supplémentaires « ecriredebut (FILE *f), ecrirearbre (FILE *f, Nœud *a), ecrirefin (FILE * f), dessine (FILE *f, Nœud *a) », ces fonctions permettent de crée un fichier PDF en sorti une fois que l’arbre est créé et donc permettre sa visualisation. Nous avons donc utilisé des fprintf pour écrire dans des fichiers, en suivant la syntaxe de DOT qui permet cette visualisation.
Pour finir une fonction « construit_arbre(Arbre *a) qui permet a l’utilisateur de saisir le parcours infixe de l’arbre dans le terminal et donc de créé et stocker cet arbre.

Dans le module greffe nous avons implémenter la fonction de copie comme demander, celle-ci copie l’arbre source vers un arbre dest.
Pour permettre la greffe nous avons ajouté des fonctions avant la fonction d’expansion. Premièrement il nous fallait une fonction « greffer fils (Arbre *n, Arbre *fg, Arbre *fd) » qui doit greffer aux feuilles du nouvel arbre greffé, l’ancien sous arbre avant la greffe, et attention il fallait parcourir l’arbre dans l’ordre suffixe sinon la fonction s’arrêtait qu’a la première feuille. Puis Nous avons mis en place la fonction Greffe (Arbre*n, Arbre* b) qui appelle la fonction d’avant et réalise la greffe complète de l’arbre B sur l’arbre N, toujours avec un parcours suffixe, pour greffer les sous arbres on utilise une copie de B. Et enfin la fonction expansion expansion (Arbre *A, Arbre B) qui prend en paramètre deux arbres et utilise la fonction greffe et vérifie si l’arbre n’est pas NULL.

Dans le module saage, nous avons développé une fonction de sérialisation serialise(const char *nom_de_fichier, Arbre A), permettant de sauvegarder la structure d'un arbre dans un fichier spécifié. Cette fonction prend en charge l'ouverture du fichier en mode écriture, suivi de l'appel d'une fonction récursive serialise_rec(FILE *f, Arbre A, int niveau) qui parcourt l'arbre en ordre suffixe. Chaque nœud est représenté dans le fichier avec ses données associées. En cas de succès, la fonction retourne 1 ; en cas d'échec, elle supprime le fichier potentiellement créé. Nous avons également la fonction int deserialise(const char * nom_de_fichier, Arbre * A), développée pour reconstruire un arbre à partir d'un fichier spécifié. La désérialisation est réalisée en ouvrant le fichier en mode lecture, suivi de l'appel d'une fonction récursive int deserialise_rec(FILE *f, Arbre *a, int niveau), qui permet la lecture en ordre suffixe du fichier. Les nœuds de l'arbre sont reconstitués en fonction des données stockées. En cas de succès, la fonction retourne 1 ; en cas d'échec, elle libère la mémoire allouée pour l'arbre et retourne 0. Cela offre une méthode efficace pour restaurer un arbre à partir d'un fichier sérialisé.
Le main, dans le main nous appelons toutes les fonctions principales qui sont demandés dans chaque modules. L'option «. /main -E [nom_du_fichier_saage]» permet à l'utilisateur de saisir un arbre interactivement, puis d'enregistrer cette structure dans un fichier au format saage, dont le nom est spécifié en ligne de commande.
Pour l’option «. /main -G[fichier_de_l’abre][fichier_de_larbre_qui_greffe ] », deux arbres sont chargés depuis des fichiers saage distincts, puis une greffe est réalisée entre ces arbres. Le résultat de cette opération est également sauvegardé dans un fichier saage, et des représentations graphiques des arbres sont générées en fichiers dot et pdf. La mémoire est gérée de manière appropriée avec des libérations après chaque opération.


