#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("ecosysteme.txt", "r"); 
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char param[50];
    int largeur_monde, hauteur_monde, nombre_proies, nombre_predateurs;

    while (fscanf(file, "%s", param) != EOF) {
        if (strcmp(param, "largeur_monde") == 0) {
            fscanf(file, "%d", &largeur_monde);
        } else if (strcmp(param, "hauteur_monde") == 0) {
            fscanf(file, "%d", &hauteur_monde);
        } else if (strcmp(param, "nombre_initial_proies") == 0) {
            fscanf(file, "%d", &nombre_proies);
        } else if (strcmp(param, "nombre_initial_predateurs") == 0) {
            fscanf(file, "%d", &nombre_predateurs);
        }
        // Ajoute d'autres paramètres si nécessaire
    }

    fclose(file);

    printf("Largeur du monde : %d\n", largeur_monde);
    printf("Hauteur du monde : %d\n", hauteur_monde);
    printf("Nombre initial de proies : %d\n", nombre_proies);
    printf("Nombre initial de prédateurs : %d\n", nombre_predateurs);

    return 0;
}
