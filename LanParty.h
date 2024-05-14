#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 15

struct Jucator{
    int points;
    char nume[L];
    char prenume[L];
};

typedef struct Jucator Player;

struct Echipa{
    int nrj; // numarul de jucatori
    char *name;
    Player *jucatori;
    struct Echipa *next;
};

typedef struct Echipa Team;

int putere2(int NumarEchipe); // functie pentru calculare N maxim
float Punctaj_Echipa(Team *team); // punctajul mediu al echipei
void delete1Team(Team **head, float medie); //functie pentru stergerea unei echipe din lista