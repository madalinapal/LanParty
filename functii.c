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

void deleteStack(SNode **top)
{
    SNode *temp;
    while((*top)!=NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

int isEmptyQ(Queue *q)
{
    return (q->front == NULL);
}
void deleteQueue(Queue *q){
    Match *aux;
    while(!isEmptyQ(q)){
        aux = q->front;
        q->front = q->front->next;
        free(aux);
    }
    free(q);
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

int height(ANode *root)
{
    int hs, hd;
    if(root == NULL)
        return 0;
    hs = height(root->left);
    hd = height(root->right);
    return 1 + ((hs>hd) ? hs:hd);
}

void printLevel (ANode *root, int level)
{
    if(root == NULL)
        return;
    if(level == 1)
         printf("%s\n", root->TeamName);
    else if(level > 1){
        printLevel(root->left, level-1);
        printLevel(root->right, level-1);
    }
}

void levelOrderTraversal(ANode *root)
{
    int h = height(root);
    int i;
    for(i = 1; i <= h; i ++)
    {
        printLevel(root, i);
        printf("\n");
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