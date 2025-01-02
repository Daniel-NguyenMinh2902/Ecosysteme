#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define MAX_ITER 200  // Nombre maximal d'itérations 
#define T_WAIT 40000 // Pause en microsecondes (40 ms) 


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


int main(void) {
    // A completer. Part 2:

    // exercice 4, question 1 & 2: 
    // Tester la fonction de déplacement avec gestion de la toricité :  
    srand(time(NULL)); // Initialisation aléatoire

    // Créer un animal unique 
    Animal *animal = creer_animal(2, 3, 90.0);
    animal->dir[0] = 1;  // Déplacement vers la droite (axe x)
    animal->dir[1] = 1;  // Déplacement vers le haut (axe y) 
    animal->suivant = NULL; 

    // l'état initial
    printf("Position initiale : (%d, %d)\n", animal->x, animal->y);

    // appeler la fonction de déplacement
    bouger_animaux(animal);

    // l'état après déplacement pour vérifier la toricité
    printf("Position après déplacement : (%d, %d)\n", animal->x, animal->y); 

    // Libérer la mémoire
    liberer_liste_animal(animal); 
    
    // Tester la fonction de reproduction 
    Animal* liste_animal = creer_animal(4, 5, 90.0);
    animal->dir[0] = -1;  
    animal->dir[1] = 1; 
    liste_animal->suivant = NULL;  

    // Taux de reproduction de 1 (100%)
    float p_reproduce = 1.0; 

    // Afficher le nombre d'animaux avant reproduction
    afficher_liste(liste_animal); 
    printf("Nombre d'animaux avant reproduction : %u\n", compte_animal_it(liste_animal)); 

    // Appeler la fonction de reproduction
    reproduce(&liste_animal, p_reproduce); 

    // Afficher le nombre d'animaux après reproduction
    afficher_liste(liste_animal); 
    printf("Nombre d'animaux avant reproduction : %u\n", compte_animal_it(liste_animal)); 

    // Libérer la mémoire
    liberer_liste_animal(liste_animal); 


    // exercice 5, question 2 
    // Initialisation du monde (taille définie par SIZE_X et SIZE_Y)
    int monde[SIZE_X][SIZE_Y] = {0};  // Le monde avec de l'herbe (initialisé à 0) 

    // Initialisation de la liste des proies et des predateurs 
    Animal* liste_proie = NULL;
    Animal* liste_predateur = NULL; 

    // creation de 20 proies à position aleatoire 
    for(int i=0; i < NB_PROIES; i++){
        int x = rand() % SIZE_X; 
        int y = rand() % SIZE_Y; 
        ajouter_animal(x, y, &liste_proie); 
    }

    // Boucle principale qui s'arrête lorsqu'il n'y a plus de proies ou après MAX_ITER (200) itérations 
    int iter = 0;
    while (liste_proie != NULL && iter < MAX_ITER) {
        printf("Iteration %d :\n", iter + 1);

        // Afficher l'état de l'écosystème (proies)
        afficher_ecosys(liste_proie, NULL);  // On affiche seulement les proies pour l'instant

        // Mise à jour des proies
        rafraichir_proies(&liste_proie, monde);

        // Pause de 40 ms (40 000 microsecondes)
        usleep(T_WAIT); 

        // Incrémenter le compteur d'itérations
        iter++;
    } 

    // Si la boucle est sortie parce qu'il n'y a plus de proies
    if (liste_proie == NULL) {
        printf("Toutes les proies sont mortes.\n");
    } else {
        printf("Nombre maximal d'itérations atteint (%d).\n", MAX_ITER);
    }

    // Libérer la mémoire allouée pour les proies
    liberer_liste_animal(liste_proie); 



    // exercice 6, question 3 
    // Initialisation de l'écosystème
    // Création de 20 proies
    for (int i = 0; i < 20; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, &liste_proie);
    }
    // Création de 10 prédateurs
    for (int i = 0; i < 10; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, &liste_predateur);
    }

    // Boucle de simulation
    int iteration = 0;
    while (iteration < MAX_ITER && liste_proie != NULL && liste_predateur != NULL) {
        // Mise à jour des proies
        rafraichir_proies(&liste_proie, monde);

        // Mise à jour des prédateurs
        rafraichir_predateurs(&liste_predateur, &liste_proie);

        // Affichage de l'écosystème
        afficher_ecosys(liste_proie, liste_predateur);

        // Pause pour voir les changements
        usleep(500000); // Pause de 500 ms 

        // Incrémenter l'itération
        iteration++;

        // Si toutes les proies ou tous les prédateurs disparaissent
        if (liste_proie == NULL) {
            printf("Toutes les proies ont disparu après %d itérations.\n", iteration);
        }
        if (liste_predateur == NULL) {
            printf("Tous les prédateurs ont disparu après %d itérations.\n", iteration);
        }
    } 

    // Libération de la mémoire
    liberer_liste_animal(liste_proie);
    liberer_liste_animal(liste_predateur); 

    // exercice 7, question 1 
    int herbe[SIZE_X][SIZE_Y];  

    // initialiser le tableau à 0 
    for(int i=0; i < SIZE_X; i++){
        for(int j=0; j < SIZE_Y; j++){ 
            herbe[i][j] = 0; 
        }
    }

    // exercice 8 
    FILE *file = fopen("Evol_Pop.txt.rft", "w"); 
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    for (int iteration = 0; iteration < MAX_ITER; iteration++) { 

        rafraichir_monde(monde);
        
        rafraichir_proies(&liste_proie, monde);
        
        rafraichir_predateurs(&liste_predateur, &liste_proie);

        int nb_proies = compte_animal_it(liste_proie);
        int nb_predateurs = compte_animal_it(liste_predateur); 

        // Écriture dans le fichier
        fprintf(file, "%d %d %d\n", iteration, nb_proies, nb_predateurs);

        // Affichage de l'écosystème
        afficher_ecosys(liste_proie, liste_predateur); 
    }

    fclose(file);
   
   /*
   utilisez: gnuplot dans Terminal pour tracer les courbes des populations 
    1. Lancer gnuplot dans le terminal :
        gnuplot 
    2. Dans l'invite de gnuplot, taper : 
        plot "Evol_Pop.txt.rft" using 1:2 with lines title "proies"
        replot "Evol_Pop.txt.rft" using 1:3 with lines title "prédateurs" 
   */

    return 0;
}



