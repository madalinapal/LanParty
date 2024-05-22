#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct AVLNode{
    int height;
    float points;
    char *TeamName;
    struct AVLNode *left, *right;
}AVLNode;

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
void printLevel (ANode *root, int level);
void levelOrderTraversal(ANode *root);
int nodeHeight(AVLNode *root);
int max(int a, int b);
AVLNode *RightRotation(AVLNode *z);
AVLNode *LeftRotation(AVLNode *z);
AVLNode* LRRotation(AVLNode *Z);
AVLNode* RLRotation(AVLNode *Z);
int comp(AVLNode* node, ANode* p);
int getHeight(AVLNode *node);
void freeAVL(AVLNode* Root);
void freeBST(ANode *root);
void freePrimele8(SNode *primele8);
void freeTeam(Team *team);
void freeTeams(Team *head);