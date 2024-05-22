#include "functii.h"

int putere2(int NumarEchipe){
    long long int N = 1;
    while( N < NumarEchipe ){
        N = N * 2;
    }
    if(N > NumarEchipe)
       return N/2;
    else
        return N;
}

float Punctaj_Echipa(Team *team)
{
    float ma = 0;
    int i;
    for( i = 0; i < team->nrj; i ++)
        ma += team->jucatori[i].points;
    ma = ma/team->nrj;
    return ma;
}

void delete1Team(Team **head, float medie){
    if(*head == NULL)
        return;
    Team *headcopy = *head;
    if(Punctaj_Echipa(headcopy) == medie)
    {
        *head = (*head)->next;
        free(headcopy);
        return;
    }
    Team *prev = *head;
    while(headcopy!=NULL){
        if(Punctaj_Echipa(headcopy) != medie){
            prev = headcopy;
            headcopy = headcopy->next;
        }
        else{
            prev->next = headcopy->next;
            free(headcopy);
            return; 
        }
    }
}

Queue* Init(){
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if(q == NULL)
        return NULL;
    q->front = q->rear = NULL;
    return q;
}

void push(SNode **top, char *name, float score)
{
    SNode *newNode = (SNode*)malloc(sizeof(SNode));
    newNode->TeamName = (char*)malloc(strlen(name)+1);
    strcpy(newNode->TeamName, name);
    newNode->points = score+1;
    newNode->next = *top;
    *top = newNode;
}
int isEmptyS(SNode *top)
{
    return top == NULL;
}

int isEmptyQ(Queue *q)
{
    return (q->front == NULL);
}


void PrintMatches(FILE *fis, Queue *q, int Runda)
{
    fprintf(fis, "\n--- ROUND NO:%d\n",Runda);
    Match *current = q->front;
    while(current!=NULL)
    {
        fprintf(fis, "%-33s-%*s\n",  current->echipa1, 33, current->echipa2);
        current = current->next;
    }
}

void PrintWinners(FILE *fis, SNode *winners, int Runda)
{
    fprintf(fis, "\nWINNERS OF ROUND NO:%d\n",Runda);
    SNode *current = winners;
    if(current == NULL)
        printf("Stiva este goala!\n");
    while(current!=NULL)
    {
        if(Runda>=3)
            {
                fprintf(fis, "%-34s-", current->TeamName);
                fprintf(fis,"  %-.2f\n", current->points);
            }
        else
            {
                fprintf(fis, "%-34s-", current->TeamName);
                fprintf(fis,"  %-.2f\n", current->points);
            }
        current = current->next;
    }
}

int nodeHeight(AVLNode *root){
    if(root == NULL)
        return -1;
    else return root->height;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

AVLNode *RightRotation(AVLNode *z)
{
    AVLNode *y = z->left;
    AVLNode *T3 = y->right;
    y->right = z;
    z->left = T3;

    z->height = max(nodeHeight(z->left), nodeHeight(z->right))+1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right))+1;

    return y;
}

AVLNode *LeftRotation(AVLNode *z)
{
    AVLNode *y = z->right;
    AVLNode *T2 = y->left;
    y->left = z;
    z->right = T2;

    z->height = max(nodeHeight(z->left), nodeHeight(z->right))+1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right))+1;

    return y;
}

AVLNode* LRRotation(AVLNode *Z)
{
    Z->left = LeftRotation(Z->left);
    return RightRotation(Z);
}

AVLNode* RLRotation(AVLNode *Z)
{
    Z->right = RightRotation(Z->right);
    return LeftRotation(Z);
}

int comp(AVLNode* node, ANode* p) {
    if(p->points < node->points)
        return -1;
    else if (p->points > node->points)
        return 1;
    else
    {
        if (strcmp(p->TeamName, node->TeamName) > 0)
            return 1;
        else
            return -1;
    }
}

int getHeight(AVLNode *node) {
    if (node == NULL)
        return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
