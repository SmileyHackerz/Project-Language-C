#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matieres.h"

void afficherMatieres(){
    system("cls");
    FILE *f = fopen("matieres.csv","r");
    if (!f)
    {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Matiere m;
    char ligne[100];

    printf("Liste des matieres : \n");
    while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%hd", &m.reference, m.libelle, &m.coefficient);

        printf(" Ref: %d | %s | Coef: %hd\n", m.reference, m.libelle, m.coefficient);
    }
    
    fclose(f);
}


void supprimerMatiere(int reference){
    system("cls");
    FILE *f = fopen("matieres.csv","r");
    FILE *temp = fopen("temp.csv","w");

    Matiere m;
    char ligne[100];
    int trouve = 0;
    if (!f || !temp)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    
     while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%hd", &m.reference, m.libelle, &m.coefficient);
        if (m.reference != reference )
        {
           fprintf(temp, "%d,%s,%hd\n", m.reference, m.libelle, m.coefficient);
        }
        else{
            trouve = 1;
        }
        
    }
    fclose(f);
    fclose(temp);

    remove("matieres.csv");
    rename("temp.csv","matieres.csv");

    if (trouve)
    {
        printf("Matiere supprimee avec succes!\n");
    }
    else
    {
        printf("Reference non trouvee!\n");
    }
      
}


void ajouterMatiere(){
    system("cls");
    FILE *f = fopen("matieres.csv","a+");
    if (!f)
    {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Matiere m;
    printf("Veuillez entrer la reference: ");
    scanf("%d", &m.reference);
    getchar();

    printf("Veuillez entrer le libelle: ");
    fgets(m.libelle, sizeof(m.libelle), stdin);
    m.libelle[strcspn(m.libelle, "\n")] = '\0';
    
    printf("Veuillez entrer le coefficient: ");
    scanf("%hd", &m.coefficient);

    fprintf(f, "%d,%s,%hd\n", m.reference, m.libelle, m.coefficient);

    fclose(f);
    printf("Matiere ajoutee avec succes.\n");
}


void modifierMatiere(int reference){
    system("cls");
    FILE *f = fopen("matieres.csv","r");
    FILE *temp = fopen("temp.csv","w");

    Matiere m;
    char ligne[100];
    int trouve = 0;

    if (!f || !temp)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%hd", &m.reference, m.libelle, &m.coefficient);

        if (m.reference == reference)
        {
            trouve = 1;
            printf(" ========================================= ");
            printf("   MODIFICATION DE LA MATIERE DE REF: %d   ", reference);
            printf(" ========================================= \n");

            getchar();

            printf("Nouveau libelle : ");
            scanf("%[^\n]", m.libelle);
            

            printf("Nouveau Coefficient: ");
            scanf("%hd", &m.coefficient);

        }
        fprintf(temp, "%d,%s,%hd\n", m.reference, m.libelle, m.coefficient);
    }

    fclose(f);
    fclose(temp);
    remove("matieres.csv");
    rename("temp.csv","matieres.csv");

    if (trouve)
    {
        printf("Matiere modifiee avec succes!\n");
    }
    else
    {
        printf("Reference non trouvee!\n");
    }
}

void rechercherMatiere(int reference){
    system("cls");
    FILE *f = fopen("matieres.csv","r");
    char ligne[100];
    Matiere m;
    int trouve = 0;

    if (!f)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), f))
    {
         sscanf(ligne, "%d,%[^,],%hd", &m.reference, m.libelle, &m.coefficient);
        if (m.reference == reference)
        {
            
            printf(" =================================== ");
            printf("           CLASSE TROUVEE            ");
            printf(" =================================== ");

            printf("Code : %d\n", m.reference);

            printf("Nom : %s\n", m.libelle);

            printf("Niveau: %hd\n", m.coefficient);
            trouve = 1;
            break;
        }
  
    }
        if(!trouve){
        printf("Matiere non trouve.\n");
    }

    fclose(f);
}