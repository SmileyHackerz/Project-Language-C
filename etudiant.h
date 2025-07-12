#ifndef etudiant_H
#define etudiant_H

typedef struct Date
{
    int jour;
    int mois;
    int annee;

} Date;

typedef struct Etudiant
{ 
    int numero;
    char nom[30];
    char prenom[50];
    char email[50];
    Date date_naissance;
    int code;

} Etudiant;

void afficherEtudiants();
void supprimerEtudiant(int numero);
void ajouterEtudiant();
void modifierEtudiant(int numero);
void rechercherEtudiant(int numero);

#endif