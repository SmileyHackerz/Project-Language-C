#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"

void afficherEtudiants(){
    system("cls");
    FILE *f = fopen("etudiants.csv","r");
    if (!f)
    {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Etudiant e;
    char ligne[200];

    printf("Liste des étudiants : \n");
    while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%[^,],%[^,],%d/%d/%d,%d", &e.numero, e.nom, e.prenom, e.email, &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee, &e.code);

        printf("%d | %s %s | %s | %02d/%02d/%04d | Classe %d\n", e.numero, e.nom, e.prenom, e.email, e.date_naissance.jour, e.date_naissance.mois, e.date_naissance.annee, e.code);
    }
    
    fclose(f);
    
}

void supprimerEtudiant(int numero){
    system("cls");
    FILE *f = fopen("etudiants.csv","r");
    FILE *temp = fopen("temp.csv","w");

    Etudiant e;
    char ligne[200];
    int trouve = 0;
    if (!f || !temp)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    
     while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%[^,],%[^,],%d/%d/%d,%d", &e.numero, e.nom, e.prenom, e.email, &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee, &e.code);
        if (e.numero != numero )
        {
           fprintf(temp, "%s", ligne);
        }
        else
        {
            trouve = 1;
        }
        
        
    }

    fclose(f);
    fclose(temp);

    remove("etudiants.csv");
    rename("temp.csv","etudiants.csv");
    if (trouve)
    {
        printf("Etudiant supprime (si existant).\n");
    }
    else
    {
        printf("Etudiant non trouve!\n");
    }
      
 
}

void ajouterEtudiant(){
    system("cls");
     FILE *f = fopen("etudiants.csv","a+");
    if (!f)
    {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Etudiant e;
    char buffer[100];

    getchar();

    printf("Veuillez entrer le numero: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &e.numero) != 1){
        printf("Numero invalide.\n");
        fclose(f);
        return;
    }

    printf("Veuillez entrer le nom: ");
    fgets(e.nom, sizeof(e.nom), stdin);
    e.nom[strcspn(e.nom, "\n")] = '\0';
    
    printf("Veuillez entrer le prenom: ");
    fgets(e.prenom, sizeof(e.prenom), stdin);
    e.prenom[strcspn(e.prenom, "\n")] = '\0';

    printf("Veuillez entrer le email: ");
    if(!fgets(e.email, sizeof(e.email), stdin)){
        printf("Erreur de lecture de l'email.\n");
        fclose(f);
        return;
    }
    e.email[strcspn(e.email, "\n")] = '\0';


    printf("Veuillez entrer le Date de naissance (jj mm aaaa): ");
    fgets(buffer, sizeof(buffer), stdin);
    if(sscanf(buffer, "%d %d %d", &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee) != 3){
        printf("Format de date invalide.\n");
        fclose(f);
        return;
    }

    printf("Veuillez entrer le code de la classe: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &e.code) != 1){
        printf("Code de la classe invalide.\n");
        fclose(f);
        return;
    }

    fprintf(f, "%d,%s,%s,%s,%02d/%02d/%04d,%d\n", e.numero, e.nom, e.prenom, e.email, e.date_naissance.jour, e.date_naissance.mois, e.date_naissance.annee, e.code );

    fclose(f);
    printf("Etudiant ajoute avec succes.\n");
}

void modifierEtudiant(int numero){
    system("cls");
    FILE *f = fopen("etudiants.csv","r");
    FILE *temp = fopen("temp.csv","w");

    Etudiant e;
    int trouve = 0;
    char buffer[100];

    if (!f || !temp)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), f)){
        sscanf(buffer, "%d,%[^,],%[^,],%[^,],%d/%d/%d,%d", &e.numero, e.nom, e.prenom, e.email, &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee, &e.code);
        if (e.numero == numero)
        {
            trouve = 1;
            printf(" =================================== ");
            printf("   MODIFICATION DE L'ETUDIANT N %d   ", numero);
            printf(" =================================== \n");

            getchar();


            printf("Nouveau Nom: ");
            fgets(e.nom, sizeof(e.nom), stdin);
            e.nom[strcspn(e.nom, "\n")] = '\0';
    
            printf("Nouveau Prenom: ");
            fgets(e.prenom, sizeof(e.prenom), stdin);
            e.prenom[strcspn(e.prenom, "\n")] = '\0';

            printf("Nouvel email: ");
            fgets(e.email, sizeof(e.email), stdin);
            e.email[strcspn(e.email, "\n")] = '\0';
            
            printf("Nouvelle date (jj mm aaaa) : ");
            fgets(buffer, sizeof(buffer), stdin);
            if(sscanf(buffer, "%d %d %d", &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee) != 3){
            printf("Format de date invalide.\n");
            fclose(f);
            fclose(temp);
            remove("temp.csv");
            return;
            }
            printf("Nouveau code de classe : ");
            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &e.code) != 1){
            printf("Code de la classe invalide.\n");
            fclose(f);
            fclose(temp);
            remove("temp.csv");
            return;
    }
        }
        fprintf(temp, "%d, %s, %s, %s, %d/%d/%d, %d\n", e.numero, e.nom, e.prenom, e.email, e.date_naissance.jour, e.date_naissance.mois, e.date_naissance.annee, e.code );
    }

    fclose(f);
    fclose(temp);
    remove("etudiants.csv");
    rename("temp.csv","etudiants.csv");

    if (trouve)
    {
        printf("Etudiant modifie avec succes.\n");
    }
    else{
        printf("Etudiant non trouve.\n");
    }
   
}

void rechercherEtudiant(int numero){
    system("cls");
    FILE *f = fopen("etudiants.csv","r");
    Etudiant e;
    int trouve = 0;

    if (!f)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fscanf(f, "%d,%[^,],%[^,],%[^,],%d/%d/%d,%d", &e.numero, e.nom, e.prenom, e.email, &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee, &e.code) == 8)
    {
        if (e.numero == numero)
        {
            
            printf(" =================================== ");
            printf("         ETUDIANT TROUVE             ");
            printf(" =================================== ");

            printf("Numero : %d\n", e.numero);

            printf("Nom : %s\n", e.nom);

            printf("Prenom : %s\n", e.prenom);

            printf("Email : %s\n", e.email);

            printf("Date de naissance : %02d/%02d/%04d\n", e.date_naissance.jour, e.date_naissance.mois, e.date_naissance.annee);

            printf("Code Classe : %d\n", e.code);

            trouve = 1;
            break;
        }
  
    }

    if(!trouve){
        printf("Etudiant non trouve.\n");
    }
    
    fclose(f);  
}