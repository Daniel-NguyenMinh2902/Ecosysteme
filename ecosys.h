#ifndef _ECOSYS_H_
#define _ECOSYS_H_

#define SIZE_X 20
#define SIZE_Y 50

#define NB_PROIES 20 
#define NB_PREDATEURS 20 

typedef struct _animal {
  int x, y;
  int dir[2]; /* direction courante sous la forme (dx, dy) */
  float energie;
  struct _animal *suivant;
}Animal; 



Animal *creer_animal(int x, int y, float energie); 
Animal *ajout_en_tete_animal(Animal* liste, Animal* animal); 
void afficher_liste(Animal* liste); 
unsigned int compte_animal_it(Animal* la); 
unsigned int compte_animal_rec(Animal* la); 

void ajouter_animal(int x, int y, Animal** liste_animal); 
Animal* liberer_liste_animal(Animal* liste);  
void enlever_animal(Animal** liste, Animal* animal); 
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur); 

void bouger_animaux(Animal* la); 
void reproduce(Animal** liste_animal, float p_reproduce); 
void rafraichir_proies(Animal** liste_proie, int monde[SIZE_X][SIZE_Y]);
Animal* animal_en_XY(Animal* l, int x, int y); 
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie); 
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]); 

void ecrire_ecosys(const char* nom_fichier, Animal* liste_predateur, Animal* liste_proie); 
void lire_ecosys(const char* nom_fichier, Animal** liste_predateur, Animal** liste_proie); 

void clear_screen(); 

#endif
