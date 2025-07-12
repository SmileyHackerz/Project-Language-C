#ifndef matiere_classe_H
#define matiere_classe_H

typedef struct Matiere_Classe
{
    int reference;
    int code;

} Matiere_Classe;

void associerMatiere_Classe(int reference, int code);
void dissocierMatiere_Classe(int reference, int code);

#endif