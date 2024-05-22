#include "functii.h"
#define Ncerinte 5

void addAtBeginning(Team **head, int v, char *nume, FILE *fis)
{
    int i;
    char linie[100];
    Team* newNode = (Team*)malloc(sizeof(Team));
    
    newNode->name = (char*)malloc((strlen(nume)+1)*sizeof(char));
    
    strcpy(newNode->name, nume); //numele echipei citite din fisier
    if(newNode->name[strlen(newNode->name)-1]==' ')
        newNode->name[strlen(newNode->name)-1]='\0';

    newNode->nrj = v; //numarul de jucatori din echipa
    
    newNode->jucatori = (Player*)malloc(v*sizeof(Player)); //aloc spatiu pentru numarul de jucatori din echipa
   
    for(i = 0; i < newNode->nrj; i ++) //introduc cei v jucatori
    {
        char *aux;
        if (fgets(linie, sizeof(linie), fis) == NULL) {
            printf("Eroare la citirea din fisier.\n");
            exit(EXIT_FAILURE);
        }
    
        aux = strtok(linie, " ");
        newNode->jucatori[i].nume = (char *)malloc((strlen(aux)+1)*sizeof(char));
        strncpy(newNode->jucatori[i].nume, aux, strlen(aux)+1);

        aux = strtok(NULL, " ");
        newNode->jucatori[i].prenume = (char *)malloc((strlen(aux)+1)*sizeof(char));
        strncpy(newNode->jucatori[i].prenume, aux, strlen(aux)+1);

        aux = strtok(NULL, " ");
        newNode->jucatori[i].points = atoi(aux);
        
    }
    newNode->next = *head;
    *head = newNode;

}

void Citire(FILE *fis1, Team **head, int *nrechipe)
{
    int  i, v;
    char line[100], *nume; 
    if(fscanf(fis1, "%d", nrechipe)!=1)//citesc nr echipe din fisier
       {
        printf("Nu se poate citi numarul de echipe\n");
       }
    
    fgets(line, sizeof(line), fis1);
    
    for( i = 0; i < *nrechipe; i ++){
        if(fgets(line, sizeof(line), fis1) == NULL)
        {
            printf("Eroare la citirea liniei\n");
        }
        
        char *aux;
        aux = strtok(line, " ");
        v = atoi(aux);

        aux = strtok(NULL, "\r\n\0");
        nume = (char *)malloc((strlen(aux)+1)*sizeof(char));
        strncpy(nume, aux, strlen(aux)+1);
        
        addAtBeginning(head, v, nume, fis1);
        free(nume);
        fgets(line, sizeof(line), fis1);
    }
}

void Afisare(FILE *fis, Team *head)
{
    Team *p;
    for( p = head; p!=NULL; p=p->next)
    {
        fprintf(fis, "%s", p->name); 
        fprintf(fis, "\n");
    }
}

float CMMPunctajEchipa(Team *head)
{
    Team *p = head;
    float medie = Punctaj_Echipa(head);
    for( p = (head)->next; p!=NULL; p = p->next)
        if(Punctaj_Echipa(p)<medie)
            medie = Punctaj_Echipa(p);
    return medie;
}

void DeleteFromTeam(Team **head, int nrechipe)
{
    Team *p;
    float punctaj; 
    int n = putere2(nrechipe);
    int NRech = nrechipe;
    while(NRech > n)
    {
        punctaj = CMMPunctajEchipa(*head);
        for(p = *head; p!=NULL; p = p->next)
        {
            if(Punctaj_Echipa(p) == punctaj)
                {
                    delete1Team(head, punctaj);
                    NRech --;
                    break;
                }
        }
    }         
}

void AdaugareElementInCoadaL(Queue *q, Team *p){
    Match *newNode = (Match*)malloc(sizeof(Match));
    newNode->echipa1 = (char*)malloc(strlen(p->name) + 1);
    newNode->echipa2 = (char*)malloc(strlen(p->next->name) + 1);
    strcpy(newNode->echipa1, p->name);
    strcpy(newNode->echipa2, (p->next)->name);
    newNode->scor1 = Punctaj_Echipa(p);
    newNode->scor2 = Punctaj_Echipa(p->next);
    newNode->next = NULL;

    if(q->rear == NULL)
        q->rear = newNode;
    else{
        (q->rear)->next = newNode;
        (q->rear) = newNode;
    }
    if(q->front == NULL)
        q->front = q->rear;
}
void AdaugareElementInCoadaS(Queue *q, SNode *p)
{
    Match *newNode = (Match*)malloc(sizeof(Match));

    newNode->echipa1 = (char*)malloc(strlen(p->TeamName) + 1);
    newNode->echipa2 = (char*)malloc(strlen(p->next->TeamName) + 1);

    strcpy(newNode->echipa1, p->TeamName);
    strcpy(newNode->echipa2, (p->next)->TeamName);

    newNode->scor1 = p->points;
    newNode->scor2 = (p->next)->points;
    newNode->next = NULL;
    
    if(q->rear == NULL)
        q->rear = newNode;
    else{
        (q->rear)->next = newNode;
        (q->rear) = newNode;
    }
    if(q->front == NULL)
        q->front = q->rear;

}
void CreateQueueL(Queue *q, Team *head)
{
    Team *p;
    for( p = head; p !=NULL; p = (p->next)->next)
        AdaugareElementInCoadaL(q, p);
}

void CreateQueueS(Queue *q, SNode *top)
{
    SNode *p;
    for( p = top; p !=NULL; p = (p->next)->next)
        AdaugareElementInCoadaS(q, p);
}

void CreateStacks(Queue *q, SNode **winners, SNode **defeated)
{
    Match *current = q->front;
    while(current!=NULL)
    {
        if(current->scor1 > current->scor2)
            {
                push(winners, current->echipa1, current->scor1);
                push(defeated, current->echipa2, current->scor2);
                current->scor1 ++;
            }
        else 
            {
                push(winners, current->echipa2, current->scor2);
                push(defeated, current->echipa1, current->scor1);
                current->scor2 ++;
            }
        current = current->next;
    }
}

void AddPrimele8inceput(SNode **head, SNode *winners) 
{
    SNode *newNode = (SNode*)malloc(sizeof(SNode));
    newNode->TeamName = (char *)malloc((strlen(winners->TeamName)+1)*sizeof(char));
    strcpy(newNode->TeamName, winners->TeamName);
    newNode->points = winners->points;

    newNode->next = *head;
    *head = newNode;
}

void AddPrimele8final(SNode **head, SNode *winners)
{
    SNode *aux = *head;
    SNode *newNode = (SNode *)malloc(sizeof(SNode));
    newNode->TeamName = (char *)malloc((strlen(winners->TeamName)+1)*sizeof(char));
    strcpy(newNode->TeamName, winners->TeamName);
    newNode->points = winners->points;

    if(*head == NULL)
        AddPrimele8inceput(&*head, winners);
    else{
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = newNode;
        newNode->next = NULL;
    }
}

ANode *newnode(SNode *p)
{
    ANode *node = (ANode *)malloc(sizeof(ANode));
    node->left = node->right = NULL;
    node->TeamName = (char *)malloc((strlen(p->TeamName)+1)*sizeof(char));
    strcpy(node->TeamName, p->TeamName);
    node->points = p->points;

    return node;
}

ANode *insert(ANode *node, SNode *p)
{
    if(node == NULL)    
        return newnode(p);
    if(p->points < node->points)
        node->left = insert(node->left, p);
    else if (p->points > node->points)
        node->right = insert(node->right, p);
    else {
        if (strcmp(p->TeamName, node->TeamName) > 0)
            node->right = insert(node->right, p);
        else
            node->left = insert(node->left, p);
    }
    return node;
}

void reverseinOrderTraversal(FILE *fis, ANode* root) {
    if (root != NULL) {
        reverseinOrderTraversal(fis, root->right);

        fprintf(fis, "%-34s-", root->TeamName);
        fprintf(fis,"  %-.2f\n", root->points);

        reverseinOrderTraversal(fis, root->left);
    }
}

AVLNode* insertavl(AVLNode* node, ANode *p)
{
    if(node == NULL){
        node = (AVLNode *)malloc(sizeof(AVLNode));
        node->TeamName = (char *)malloc((strlen(p->TeamName)+1)*sizeof(char));
        strcpy(node->TeamName, p->TeamName);
        node->points = p->points;
        node->height = 0;
        node->left = node->right = NULL;
        return node;
    }
    if(p->points < node->points)
        node->left = insertavl(node->left, p);
    else if (p->points > node->points)
        node->right = insertavl(node->right, p);
    else
    {
        if (strcmp(p->TeamName, node->TeamName) > 0)
            node->right = insertavl(node->right, p);
        else
            node->left = insertavl(node->left, p);
    }

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
    int k = (nodeHeight(node->left)-nodeHeight(node->right));
    if(k > 1 && comp(node->left, p) < 0)// p->points < node->left->points)
        return RightRotation(node);
    if(k < -1 && comp(node->right, p) > 0)// p->points > node->right->points)
        return LeftRotation(node);
    if(k > 1 && comp(node->left, p) > 0) //p->points > node->left->points)
        return RLRotation(node);
    if(k < -1 && comp(node->right, p) < 0)// p->points < node->right->points)
        return LRRotation(node);
    return node;
}

void creezAVL(AVLNode **Root, ANode *root)
{
    if (root != NULL) {
        creezAVL(Root, root->right);
        *Root = insertavl(*Root, root);
        creezAVL(Root, root->left);
    }
}

void printLevelNodes(FILE *fis, AVLNode *Root, int level) {
    if (Root == NULL) return;
    if (level == 0) {
        fprintf(fis, "%s\n", Root->TeamName);
    } else {
        printLevelNodes(fis, Root->right, level - 1);
        printLevelNodes(fis, Root->left, level - 1);
    }
}

int main(int argc, char *argv[])
{
    FILE *fis1, *fis2, *fis3;
    Team *head = NULL;
    int cerinte[Ncerinte], i, nrechipe;
    Queue *q;
    SNode *winners = NULL, *defeated = NULL; //tops pt stivele de castigatori, invinsi
    SNode *primele8 = NULL; // head-ul listei pentru primele 8 echipe 
    q = Init();
    ANode *root = NULL;
    AVLNode *Root = NULL;

    fis1 = fopen(argv[2], "r");
    fis2 = fopen(argv[3], "w");
    fis3 = fopen(argv[1], "r");

    if(fis1 == NULL)
    {
        printf("Fisierul nu poate fi deschis pentru citire\n");
        exit(1);
    }
    if(fis2 == NULL)
    {
        printf("Fisierul nu poate fi deschis pentru scriere\n");
        exit(1);
    }
    if(fis3 == NULL)
    {
        printf("Fisierul nu poate fi deschis pentru citire\n");
        exit(1);
    }

    for( i = 0; i < Ncerinte; i ++)
        fscanf(fis3, "%d", &cerinte[i]);

    if(cerinte[0])//cerinta 1
        Citire(fis1, &head, &nrechipe);

    if(cerinte[1])//cerinta 2
        DeleteFromTeam(&head, nrechipe);
       
    Afisare(fis2, head);

    if(cerinte[2])//cerinta 3
    {
        int n = putere2(nrechipe), index = 1;
        while(n > 1)
        {
            if(n == putere2(nrechipe))
            {
                CreateQueueL(q, head);
                PrintMatches(fis2, q, index);
                CreateStacks(q, &winners, &defeated);
                PrintWinners(fis2, winners, index);}
            else
            {
                deleteQueue(q);
                q = Init();
                CreateQueueS(q, winners);
                PrintMatches(fis2, q, index);
                deleteStack(&winners);
                winners = NULL;
                deleteStack(&defeated);
                defeated = NULL;
                CreateStacks(q, &winners, &defeated);
                PrintWinners(fis2, winners, index);
            }
            if(n == 16)
                for(SNode *p = winners; p!=NULL; p = p->next)
                   AddPrimele8final(&primele8, p);
                   
            n = n/2;
            index ++;
        }
    }
    
    if(cerinte[3]) //cerinta 4
    {
         for(SNode *p = primele8; p!=NULL; p = p->next)
                    root = insert(root, p);
        fprintf(fis2, "\nTOP 8 TEAMS:\n");
        reverseinOrderTraversal(fis2, root);
    }
   
    if(cerinte[4]) //cerinta 5
    {
        creezAVL(&Root, root);
        fprintf(fis2, "\nTHE LEVEL 2 TEAMS ARE:\n");
        printLevelNodes(fis2, Root, 2);
    }

    
    freeTeams(head);
    deleteStack(&defeated);
    deleteStack(&winners);
    freePrimele8(primele8);
    freeBST(root);
    freeAVL(Root);

    fclose(fis1);
    fclose(fis2);
    fclose(fis3);
    return 0;
}