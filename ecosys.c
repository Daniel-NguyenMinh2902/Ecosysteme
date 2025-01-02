#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<assert.h> 
#include<time.h> 
#include "ecosys.h"  

/* PARTIE 1*/

// La fonction de creation d’un element de type Animal
Animal *creer_animal(int x, int y, float energie){
    // Allocation dynamique de Animal 
    Animal* nouv_animal = malloc(sizeof(Animal)); // <=> Animal* nouv_animal = (Animal*)malloc(sizeof(Animal)) 
    assert(nouv_animal != NULL); // verifier si malloc fonctionne 

    // Initialisation des valeurs aux champs 
    nouv_animal->x = x; 
    nouv_animal->y = y; 
    nouv_animal->energie = energie; 

    // Initialisation des valeurs aleatoires au tableau dir
    nouv_animal->dir[0] = (rand()%3)-1; 
    nouv_animal->dir[1] = (rand()%3)-1; 

    nouv_animal->suivant = NULL; 

    return nouv_animal; 
}

// La fonction ajout animal en tête dans la liste chainee
Animal *ajout_en_tete_animal(Animal* liste, Animal* animal){
    assert(animal != NULL); // verifier si animal n'est pas NULL 
    assert(!animal->suivant); // verifier si animal suivant n'est pas NULL 
    animal->suivant = liste; // ajouter animal en tête de la liste
    return animal; // retourner 
} 

void afficher_liste(Animal* liste){
    Animal* temp = liste;  
    while(temp != NULL){
        printf("Proie à position: (%d, %d), l'energie: %.2f\n", temp->x, temp->y, temp->energie); 
        temp = temp->suivant; 
    }
    printf("\n");

}

/* A faire. Part 1, exercice 6, question 2 */ 
// une fonction permettant d’ajouter un animal a la position x, y 
void ajouter_animal(int x, int y, Animal** liste_animal){
    // verification si les coordonnees sont corrects
    assert(x >= 0 && x < SIZE_X); 
    assert(y >= 0 && y < SIZE_Y); 
    assert(liste_animal != NULL); 

    Animal* new_animal = creer_animal(x, y, 90.0); 
    assert(new_animal != NULL); 

    // ajouter new_animal en tête de liste_animal
    new_animal->suivant = *liste_animal; 
    *liste_animal = new_animal; 
}

/* A Faire. Part 1, exercice 5, question 5 */ 
// la fonction enleve un element de la liste chaınee et libere la memoire associee
void enlever_animal(Animal** liste, Animal* animal){
    
    assert(liste != NULL && animal != NULL); 

    Animal* prec = NULL; 
    Animal* courant = *liste; 

    // parcourir la liste pour trouver l'animal à supprimer 
    while(courant != NULL && courant != animal){
        prec = courant;
        courant = courant->suivant; 
    }

    // l'animal n'est pas trouvé
    if(courant == NULL){
        return;   
    }

    // si l'animal est en tête 
    if(prec == NULL){ 
        *liste = courant->suivant; 
    }else{
        prec->suivant = courant->suivant; 
    }
    free(courant); 
}

/* A Faire. Part 1, exercice 6, question 7 */ 
// Liberer animal 
Animal* liberer_liste_animal(Animal* liste){ 
    Animal* ani = liste; 
    Animal* tmp; 
    while(ani != NULL){  
        tmp = ani; 
        ani = ani->suivant; 
        free(tmp);   
    }
    return NULL; 
}

/* Fourni: part 1, exercice 4, question 4 */ 
// fonctions permettant de compter le nombre d’elements contenus dans une liste chaınee 

// fonction iterative: 
unsigned int compte_animal_it(Animal* la){
    unsigned int compte = 0; 
    while(la != NULL){
        compte++; 
        la = la->suivant; 
    }
    return compte; 
}

// fonction recursive: 
unsigned int compte_animal_rec(Animal* la){
    if(la == NULL){
        return 0;
    }else{
        return 1 + compte_animal_rec(la->suivant); 
    }
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
    unsigned int i, j;
    char ecosys[SIZE_X][SIZE_Y];
    Animal *pa=NULL;

    /* on initialise le tableau */
    for (i = 0; i < SIZE_Y; ++i) {
        for (j = 0; j < SIZE_X; ++j) {
        ecosys[i][j]=' ';
        }
    }

    /* on ajoute les proies */
    pa = liste_proie;
    while (pa) {
        ecosys[pa->x][pa->y] = '*';
        pa=pa->suivant;
    }

    /* on ajoute les predateurs */
    pa = liste_predateur;
    while (pa) {
        if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
            ecosys[pa->x][pa->y] = '@'; 
        } else {
            ecosys[pa->x][pa->y] = 'O';
        }
        pa = pa->suivant;
    } 
    /* on affiche le tableau */
    printf("+");
    for (j = 0; j < SIZE_X; ++j) {
        printf("-");
    }  
    printf("+\n");
    for (i = 0; i < SIZE_Y; ++i) {
        printf("|");
        for (j = 0; j < SIZE_X; ++j) {
        putchar(ecosys[i][j]);
        }
        printf("|\n");
    }
    printf("+"); 
    for (j = 0; j<SIZE_X; ++j) {
        printf("-");
    }
    printf("+\n");
    int nbproie=compte_animal_it(liste_proie);
    int nbpred=compte_animal_it(liste_predateur);
    
    printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}

void clear_screen() {
    printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
} 


/* PARTIE 2*/

// Deplacement et reproduction

/* Part 2. Exercice 4, question 1 */
// faire bouger tous les animaux contenus dans la liste 
void bouger_animaux(Animal* la){ 
    // taille du monde 
    int largeur_monde = 100; 
    int hauteur_monde = 100;  
    int rand_max = 100; 
    double p_ch_dir = 0.1; // probabilité de changement de direction 

    Animal* courrant = la; 

    while(courrant != NULL){
        // probabilite de changement de direction 
        if((rand() / rand_max) < p_ch_dir){ 
            // générer un nombre aleatoire entre -1 et 1 pour la direction 
            courrant->dir[0] = rand()%3 - 1; 
            courrant->dir[1] = rand()%3 - 1; 
        }

        // deplacement selon la direction 
        courrant->x = (courrant->x + courrant->dir[0]) % largeur_monde; 
        courrant->y = (courrant->y + courrant->dir[1]) % hauteur_monde; 

        // les coordonnées sont positives 
        if(courrant->x < 0){
            courrant->x += largeur_monde; 
        }
        if(courrant->y < 0){
            courrant->y += hauteur_monde; 
        }

        courrant = courrant->suivant; 
    }
}

/* Part 2. Exercice 4, question 3 */ 
// fonction permettant de gerer la reproduction des animaux 
void reproduce(Animal** liste_animal, float p_reproduce){ 
    /*
    simuler la reproduction, potentiellement en ajoutant des animaux à la liste:
    insérer de nouveaux animaux, souvent en utilisant la fonction ajouter_animal, 
    qui modifie la tête de liste si un nouvel animal est ajouté.
    */
    Animal* courrant = *liste_animal; 
    int rand_max = 100; 
    while(courrant != NULL){
        // générer une probabilité aléatoire
        float random_proba = rand()/(float)rand_max; 

        // vérifier la probabilité de reproduction 
        if(random_proba < p_reproduce){
            // un nouvel animal à la même position que le parent dont l'energie la moitie de celle de son parent 
            float energie_enfant = courrant->energie / 2; 

            // ajouter le nouvel animal en tête de liste 
            Animal* new_animal = creer_animal(courrant->x, courrant->y, energie_enfant); 
            new_animal->suivant = *liste_animal; 
            *liste_animal = new_animal; 

            // le parent a son energie divisee par 2
            courrant->energie = courrant->energie / 2; 
        }
        courrant = courrant->suivant; 
    }
}

/* Part 2. Exercice 5, question 1 + Exercice 7 */
// fonction de mise à jour des proies 
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*
    Cette fonction devra :
    — faire bouger les proies en appelant la fonction bouger animaux;
    — parcourir la liste de proies :
        — baisser leur energie de 1,
        — supprimer les proies dont l’energie est inferieure a 0; 
    — faire appel `a la fonction de reproduction.
    */
    /*
    certaines proies peuvent mourir et être supprimées de la liste. 
    Cela nécessite de pouvoir mettre à jour la tête de liste si la première proie est supprimée.
    */
    // bouger les proies
    bouger_animaux(*liste_proie);

    // Taux de reproduction de 1 (100%)
    float p_reproduce_proie = 0.1;  

    // le temps de repousse à une valeur négative
    int temps_repousse_herbe = -15;   
    
    // Parcourir la liste des proies pour gérer l'énergie et supprimer les proies mortes
    Animal *prec = NULL;  // Pointeur pour garder la trace du précédent animal
    Animal *courrant = *liste_proie;  // Pointeur sur la proie actuelle (courrant) 
    
    while (courrant != NULL) { 
        // Déplacement de l'animal
        bouger_animaux(courrant); 

        // baisser l'énergie de 1
        courrant->energie -= 1; 

        // vérification de l'herbe sur la case
        int x = courrant->x;
        int y = courrant->y; 

        if (monde[x][y] > 0) {
            // animal mange l'herbe et gagne des points d'énergie
            courrant->energie += monde[x][y];
            // herbe est consommee, on met le temps de repousse à une valeur négative
            monde[x][y] = temps_repousse_herbe; 
        }
        
        // supprimer la proie si son énergie de la proie est inférieure à 0 (morte)
        if (courrant->energie <= 0) { 
            Animal *animal_sup = courrant; 
            
            if (prec == NULL) {
                // Suppression en tête de liste
                *liste_proie = courrant->suivant; 
            } else {
                // Suppression en milieu ou fin de liste
                prec->suivant = courrant->suivant; 
            }
            courrant = courrant->suivant;  // Passer à la proie suivante 
            free(animal_sup);  // Libérer la mémoire de l'animal supprimé 
        } else {
            // continuer à parcourir la liste 
            prec = courrant;
            courrant = courrant->suivant; 
        }
    }

    // Reproduction des proies
    reproduce(liste_proie, p_reproduce_proie); 
}


/* Part 2. Exercice 6, question 1 */ 
// fonction qui gere les predateurs en verifiant s'il y a une proie sur une case donnee 
Animal* animal_en_XY(Animal *l, int x, int y) { 
    /* la valeur de retour est un pointeur sur une proie dont les coordonnees sont x et y ou NULL sinon. */ 
    // la liste des proies
    Animal *courrant = l; 

    // Parcourt la liste chaînée des animaux (proies dans ce cas)
    while (courrant != NULL) { 
        // Vérifie si l'animal est à la position (x, y)
        if (courrant->x == x && courrant->y == y) {
            return courrant;  // Retourne le pointeur vers la proie trouvée
        }
        courrant = courrant->suivant;  // Passe à l'animal suivant 
    }

    return NULL;  // Aucune proie trouvée à la position (x, y)
} 

/* Part 2. Exercice 6, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
    // Déplacer tous les prédateurs
    bouger_animaux(*liste_predateur); 

    // Taux de reproduction de 1 (100%)
    float p_reproduce_predateur = 0.1;   

    Animal *prev = NULL;
    Animal *courrant = *liste_predateur; 

    while (courrant != NULL) {
        // Décrémenter l'énergie du prédateur
        courrant->energie -= 1;

        // Chercher une proie à la même position (current->x, current->y)
        Animal *proie = animal_en_XY(*liste_proie, courrant->x, courrant->y);

        if (proie != NULL) {
            // Si une proie est trouvée, le prédateur mange la proie et récupère son énergie
            courrant->energie += proie->energie;

            // Supprimer la proie de la liste des proies
            enlever_animal(liste_proie, proie);
        }

        // Si le prédateur n'a plus d'énergie, il doit être supprimé
        if (courrant->energie <= 0) {
            if (prev == NULL) {
                *liste_predateur = courrant->suivant;  // Le premier prédateur est supprimé
                free(courrant);  // Libérer la mémoire du prédateur
                courrant = *liste_predateur;  // Réinitialiser current à la tête de la liste
            } else {
                prev->suivant = courrant->suivant;  // Supprimer le prédateur dans la liste
                free(courrant);  // Libérer la mémoire du prédateur
                courrant = prev->suivant;  // Passer au suivant
            }
        } else {
            // Passer au prédateur suivant
            prev = courrant;
            courrant = courrant->suivant; 
        }
    }
    // Reproduction des prédateurs
    reproduce(liste_predateur, p_reproduce_predateur);

}

/* Part 2. Exercice 7, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) {
    for (int i = 0; i < SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            // Incrémente la quantité d'herbe sur chaque case
            monde[i][j] += 1;
        }
    }
}


// Lecture / ecriture de fichiers

// la fonction ecrire_ecosys ecrit ce fichier a partir des listes de proies et de predateurs.
void ecrire_ecosys(const char* nom_fichier, Animal* liste_predateur, Animal* liste_proie){
    FILE* f = fopen(nom_fichier, "w"); 
    if(f == NULL){
        perror("Erreur d'ouverture du fichier."); 
        return; 
    }

    fprintf(f, "<proies>\n"); 
    Animal* proie = liste_proie; 
    while(proie != NULL){
        fprintf(f, "x=%d y=%d dir=[%d %d] e=%f\n", proie->x, proie->y, proie->dir[0], proie->dir[1], proie->energie); 
        proie = proie->suivant; 
    }
    fprintf(f, "</proies>\n"); 

    fprintf(f, "<predateurs>\n"); 
    Animal* predateur = liste_predateur;  
    while(predateur != NULL){
        fprintf(f, "x=%d y=%d dir=[%d %d] e=%f\n", predateur->x, predateur->y, predateur->dir[0], predateur->dir[1], predateur->energie); 
        predateur = predateur->suivant; 
    }
    fprintf(f, "</predateurs>\n");  

    fclose(f); 
}

// la fonction lire_ecosys lit ce fichier et retourne les listes de proies et de predateurs qui ont été lues
void lire_ecosys(const char* nom_fichier, Animal** liste_predateur, Animal** liste_proie){
    FILE* f = fopen(nom_fichier, "r"); 
    if(f == NULL){
        perror("Erreur d'ouverture du fichier."); 
        return; 
    }

    char ligne[100]; 
    int x, y, dir[2];
    float energie;  

    // lecture du fichier ligne par ligne 
    while(fgets(ligne, sizeof(ligne), f) != NULL){
        if(strstr(ligne, "<proies>") != NULL){
            while(fgets(ligne, sizeof(ligne), f) != NULL && strstr(ligne, "<proies>") == NULL){
                sscanf(ligne, "x=%d y=%d dir=[%d %d] e=%f", &x, &y, &dir[0], &dir[1], &energie);
                ajouter_animal(x, y, liste_proie); 
            }
        }else if(strstr(ligne, "<predateurs>") != NULL){
            while(fgets(ligne, sizeof(ligne), f) != NULL && strstr(ligne, "<predateurs>") == NULL){
                sscanf(ligne, "x=%d y=%d dir=[%d %d] e=%f", &x, &y, &dir[0], &dir[1], &energie);
                ajouter_animal(x, y, liste_predateur);  
            }
        }
    }

    fclose(f); 
}

