#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere_classe.h"

void associerMatiere_Classe(int reference, int code){
    system("cls");
    FILE *f = fopen("matiere_classe.csv","a+");
     if (!f)
    {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }
    rewind(f);

    Matiere_Classe mc;
    char ligne[50];

    while (fgets(ligne, sizeof(ligne), f))
    {
    sscanf(ligne, "%d,%d", &mc.reference, &mc.code);
    if (mc.reference == reference && mc.code == code)
        {
           printf("Cette association existe deja!\n");

        fclose(f);
        return;
        }
    }

    fprintf(f, "%d,%d\n", reference, code);
    printf("Association ajoutee avec succes!\n");
    fclose(f);
}
    

void dissocierMatiere_Classe(int reference, int code){
    system("cls");
    FILE *f = fopen("matiere_classe.csv","r");
    FILE *temp = fopen("temp.csv","w");

    Matiere_Classe mc;
    char ligne[50];
    int trouve = 0;
    if (!f || !temp)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    
     while (fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne, "%d,%d", &mc.reference, &mc.code);
        if (mc.reference == reference && mc.code == code)
        {
           trouve = 1;
        }
        else{
             fprintf(temp, "%d,%d\n", reference, code);
        }
        
    }
    fclose(f);
    fclose(temp);

    remove("matiere_classe.csv");
    rename("temp.csv","matiere_classe.csv");

    if (trouve)
    {
        printf("Association non trouvee!\n");
    }
    else
    {
        printf("Matiere supprimee avec succes!\n");
    }
      
}