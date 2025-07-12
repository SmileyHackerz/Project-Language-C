#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

void afficherClasses(){
    system("cls");
    FILE *f = fopen("classes.csv","r");
    if (!f)
    {
        printf("Aucune classe trouvee!.\n");
        return;
    }

    Classe c;
    char ligne[100], niveautexte[20];

    printf("Liste des classes : \n");
    while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%s", &c.code, c.nom, &niveautexte);
        c.niveau = (strcmp(niveautexte, "Licence") == 0) ? Licence : Master;

        printf("Code : %d | Nom : %s | Niveau : %s\n", c.code, c.nom, (c.niveau == Licence) ? "Licence" : "Master");
    }
    
    fclose(f);
}

void supprimerClasse(int code){
    system("cls");
    FILE *f = fopen("classes.csv","r");
    FILE *temp = fopen("temp.csv","w");

    Classe c;
    char ligne[100], niveautexte[20];
    int trouve = 0;
    if (!f || !temp)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    
     while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%s", &c.code, c.nom, &niveautexte);
        c.niveau = (strcmp(niveautexte, "Licence") == 0) ? Licence : Master;
        if (c.code != code )
        {
           fprintf(temp, "%d,%s,%s\n", c.code, c.nom, (c.niveau == Licence) ? "Licence" : "Master");
        }
        else
        {
            trouve = 1;
        }
        
    }

    fclose(f);
    fclose(temp);

    remove("classes.csv");
    rename("temp.csv","classes.csv");

    if (trouve)
    {
        printf("Classe %d supprimee avec succes!\n", code);
    }
    else
    {
        printf("Classe non trouvee!\n");
    }
    
}

void ajouterClasse(){
    system("cls");
    FILE *f = fopen("classes.csv","a+");
    if (!f)
    {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Classe c;
    char niveautexte[20];
    printf("Veuillez entrer le code: ");
    scanf("%d", &c.code);
    getchar();

    printf("Veuillez entrer le nom: ");
    fgets(c.nom, sizeof(c.nom), stdin);
    c.nom[strcspn(c.nom, "\n")] = '\0';
    
    printf("Veuillez entrer le niveau (Licence/Master): ");
    fgets(niveautexte, sizeof(niveautexte), stdin);
    niveautexte[strcspn(niveautexte, "\n")] = '\0';

    if(strcmp(niveautexte, "Licence") == 0){
        c.niveau = Licence;
    }
    else{
        c.niveau = Master;
    }

    fprintf(f, "%d,%s,%s\n", c.code, c.nom, (c.niveau == Licence) ? "Licence" : "Master");

    fclose(f);
    printf("Classe ajoutee avec succes.\n");
}

void modifierClasse(int code){
    system("cls");
    FILE *f = fopen("classes.csv","r");
    FILE *temp = fopen("temp.csv","w");

    Classe c;
    char ligne[100], niveautexte[20];
    int trouve = 0;

    if (!f || !temp)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%s", &c.code, c.nom, &niveautexte);
        c.niveau = (strcmp(niveautexte, "Licence") == 0) ? Licence : Master;

        if (c.code == code)
        {
            trouve = 1;
            printf(" =================================== ");
            printf("   MODIFICATION DE LA CLASSE N %d   ", code);
            printf(" =================================== \n");

            getchar();

            printf("Nouveau nom : ");
            scanf("%[^\n]", c.nom);

            printf("Nouveau niveau (Licence/Master): ");
            scanf("%s", niveautexte);
            c.niveau = (strcmp(niveautexte, "Licence") == 0) ? Licence : Master;

        }
        fprintf(temp, "%d,%s,%s\n", c.code, c.nom, (c.niveau == Licence) ? "Licence" : "Master");
    }

    fclose(f);
    fclose(temp);
    remove("classes.csv");
    rename("temp.csv","classes.csv");

    if (trouve)
    {
        printf("Classe %d modifiee avec succes.\n", code);
    }
    else{
        printf("Classe %d non trouvee.\n", code);
    }
}

void rechercherClasse(int code){
    system("cls");
    FILE *f = fopen("classes.csv","r");
    Classe c;
    char ligne[100], niveautexte[20];
    int trouve = 0;

    if (!f)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%[^,],%s", &c.code, c.nom, &niveautexte);
        c.niveau = (strcmp(niveautexte, "Licence") == 0) ? Licence : Master;
        if (c.code == code)
        {
            
            printf(" =================================== ");
            printf("           CLASSE TROUVEE            ");
            printf(" =================================== ");

            printf("Code : %d\n", c.code);

            printf("Nom : %s\n", c.nom);

            printf("Niveau: %s\n", niveautexte);
            trouve = 1;
            break;
        }
  
    }

        if(!trouve){
        printf("Classe %d non trouve.\n", code);
    }

    fclose(f);
}