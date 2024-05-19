#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 15

struct Jucator{
    int points;
    char *nume;
    char *prenume;
};

typedef struct Jucator Player;

struct Echipa{
    int nrj; // numarul de jucatori
    char *name;
    Player *jucatori;
    struct Echipa *next;
};

typedef struct Echipa Team;

struct M{
    char *echipa1, *echipa2;
    float scor1, scor2;
    struct M *next;
};
typedef struct M Match;

struct Q{
    Match *front, *rear;
};

typedef struct Q Queue;

struct Node{
    char *TeamName;
    float points;
    struct Node *next;
};

typedef struct Node SNode;

struct N{
    char *TeamName;
    float points;
    struct N *left, *right;
};
typedef struct N ANode;

int putere2(int NumarEchipe); // functie pentru calculare N maxim
float Punctaj_Echipa(Team *team); // punctajul mediu al echipei
void delete1Team(Team **head, float medie); //functie pentru stergerea unei echipe din lista
Queue* Init();
void push(SNode **top, char *name, float score);
int isEmpty(SNode *top);
void deleteStack(SNode **top);
int isEmptyQ(Queue *q);
void deleteQueue(Queue *q);
void PrintMatches(FILE *fis, Queue *q, int Runda);
void PrintWinners(FILE *fis, SNode *winners, int Runda);