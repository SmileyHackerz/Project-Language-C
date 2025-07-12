#ifndef classes_H
#define classes_H

typedef enum Niveau {
    Licence,
    Master
} Niveau;

typedef struct Classe
{ 
    int code;
    char nom[50];
    Niveau niveau;
    
} Classe;

void afficherClasses();
void supprimerClasse(int code);
void ajouterClasse();
void modifierClasse(int code);
void rechercherClasse(int code);

#endif