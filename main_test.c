#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<assert.h> 
#include<time.h> 
#include "ecosys.h" 


#define NB_PROIES 20 
#define NB_PREDATEURS 20  

int main(){
    Animal* liste_proie = NULL; 
    Animal* liste_predateur = NULL; 

    // initialisation du generateur de nb aleatoire 
    srand(time(NULL)); 

    // creation de 20 proies à position aleatoire 
    for(int i=0; i < NB_PROIES; i++){
        int x = rand() % SIZE_X; 
        int y = rand() % SIZE_Y; 
        ajouter_animal(x, y, &liste_proie); 
    }

    // creation de 20 predateurs à position aleatoire 
    for(int j=0; j < NB_PREDATEURS; j++){
        int a = rand() % SIZE_X; 
        int b = rand() % SIZE_Y; 
        ajouter_animal(a, b, &liste_predateur);
    } 

    // verification de nombre d'animal crées 
    printf("Nombre de proies crées: %u\n", compte_animal_it(liste_proie)); 
    printf("Nombre de predateurs crées: %u\n", compte_animal_it(liste_predateur)); 
    printf("\n"); 

    // afficher les proies 
    afficher_liste(liste_proie);  

    // afficher les predateurs 
    afficher_liste(liste_predateur); 

    // supprimer quelques proies et predateurs 
    if(liste_proie != NULL){
        enlever_animal(&liste_proie, liste_proie); 
    }
    if(liste_predateur != NULL){
        enlever_animal(&liste_predateur, liste_predateur); 
    }

    printf("Nombre de proies apres la suppression: %u\n", compte_animal_it(liste_proie)); 
    printf("Nombre de predateurs apres la suppression: %u\n", compte_animal_it(liste_predateur));     

    // liberer memoire 
    liberer_liste_animal(liste_proie); 
    liberer_liste_animal(liste_predateur); 
   
    printf("Nombre de proies: %u\n", compte_animal_it(liste_proie)); 
    printf("Nombre de predateurs: %u\n", compte_animal_it(liste_predateur)); 


    // Ecriture de l'écosystème dans un fichier
    const char *nom_fichier = "ecosysteme.txt";
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

