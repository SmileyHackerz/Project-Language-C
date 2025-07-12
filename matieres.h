#ifndef matieres_H
#define matieres_H

typedef struct Matiere
{ 
    int reference;
    char libelle[100];
    short coefficient;

} Matiere;

void afficherMatieres();
void supprimerMatiere(int reference);
void ajouterMatiere();
void modifierMatiere(int reference);
void rechercherMatiere(int reference);

#endif