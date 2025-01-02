#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h" 

int main() {
    // Création des listes de proies et de prédateurs
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;

    // Ajout d'animaux dans la liste de proies 
    ajouter_animal(&liste_proie, creer_animal(8, 43, 10.0));
    ajouter_animal(&liste_proie, creer_animal(18, 38, 10.0));
    ajouter_animal(&liste_proie, creer_animal(9, 37, 10.0));

    // Ajout d'animaux dans la liste de prédateurs 
    ajouter_animal(&liste_predateur, creer_animal(14, 32, 10.0));
    ajouter_animal(&liste_predateur, creer_animal(13, 40, 10.0));
    ajouter_animal(&liste_predateur, creer_animal(18, 46, 10.0));

    // Ecriture de l'écosystème dans un fichier
    const char *nom_fichier = "ecosysteme.txt.rft"; 
    ecrire_ecosys(nom_fichier, liste_predateur, liste_proie);

    // Libérer les listes d'animaux d'origine pour simuler une nouvelle lecture
    liberer_liste_animal(liste_proie);
    liberer_liste_animal(liste_predateur);
    liste_proie = NULL;
    liste_predateur = NULL;

    // Lire l'écosystème à partir du fichier
    lire_ecosys(nom_fichier, &liste_predateur, &liste_proie);

    // Affichage pour vérification
    printf("Proies après lecture du fichier:\n");
    afficher_liste(liste_proie);  

    printf("Prédateurs après lecture du fichier:\n");
    afficher_liste(liste_predateur);  

    // Libérer les listes d'animaux après la lecture pour éviter des fuites
    liberer_liste_animal(liste_proie);
    liberer_liste_animal(liste_predateur);

    // Utiliser Valgrind pour vérifier qu'il n'y a pas de fuites mémoire
    return 0; 
}
