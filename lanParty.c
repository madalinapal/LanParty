#include "LanParty.h"
#define L 15
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

void freeTeam(Team *team) {
    if (team) {
        free(team->name);
         if (team->jucatori) {
            for (int i = 0; i < team->nrj; i++) {
                free(team->jucatori[i].nume);
                free(team->jucatori[i].prenume);
            }
            free(team->jucatori);
        
    }
        free(team);
    }
}

void freeTeams(Team *head) {
    Team *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        freeTeam(tmp);
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

void PrintMatches(FILE *fis, Queue *q, int Runda)
{
    fprintf(fis, "\n--- ROUND NO:%d\n",Runda);
    Match *current = q->front;
    while(current!=NULL)
    {
        fprintf(fis, "%-33s-%*s\n",  current->echipa1, 33, current->echipa2);
        //fprintf(fis, "%-30s - %-30s\n", current->echipa1, current->echipa2);

        current = current->next;
    }
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


int main(int argc, char *argv[])
{
    FILE *fis1, *fis2, *fis3;
    Team *head = NULL;
    int cerinte[Ncerinte], i, nrechipe;
    Queue *q;
    SNode *winners = NULL, *defeated = NULL;
    q = Init();

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

    if(cerinte[0])
        Citire(fis1, &head, &nrechipe);

    if(cerinte[1])
        DeleteFromTeam(&head, nrechipe);
       
    Afisare(fis2, head);
    if(cerinte[2])
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
            n = n/2;
            index ++;
        }
    }

    /*if(cerinte[3])
    {

    }

    if(cerinte[4])
    {

    }*/
freeTeams(head);
    fclose(fis1);
    fclose(fis2);
    fclose(fis3);
    return 0;
}