#include "LanParty.h"
#define L 15


void addAtBeginning(Team **head, int v, char nume[100], FILE *fis)
{
    int i;
    char linie[100];
    Team* newNode = (Team*)malloc(sizeof(Team));
    
    newNode->name = (char*)malloc((strlen(nume)+1)*sizeof(char));
    strcpy(newNode->name, nume); //numele echipei citite din fisier
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
        strcpy(newNode->jucatori[i].nume, aux);

        aux = strtok(NULL, " ");
        strcpy(newNode->jucatori[i].prenume, aux);

        aux = strtok(NULL, " ");
        newNode->jucatori[i].points = atoi(aux);
        
    }
    newNode->next = *head;
    *head = newNode;

}


int main(int argc, char *argv[])
{
    FILE *fis1, *fis2, *fis3;
    char line[100], nume[100]; 

    fis1 = fopen(argv[2], "r");
    fis2 = fopen(argv[3], "w");
    fis3 = fopen(argv[1], "r");

    Team *head, *p;
    int v, nrechipe, i;

    head = NULL;

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
    if(fscanf(fis1, "%d", &nrechipe)!=1)//citesc nr echipe din fisier
       {
        printf("Nu se poate citi numarul de echipe\n");
        return 0;
       }
    fgets(line, sizeof(line), fis1);
    
    for( i = 0; i < nrechipe; i ++){
        if(fgets(line, sizeof(line), fis1) == NULL)
        {
            printf("Eroare la citirea liniei");
            return 0;
        }
        
        char *aux;
        aux = strtok(line, " ");
        v = atoi(aux);

        aux = strtok(NULL, "\r\n\0");
        strcpy(nume, aux);
        
        addAtBeginning(&head, v, nume, fis1);
        fgets(line, sizeof(line), fis1);
        
    }
    
    for( p = head; p!=NULL; p=p->next)
    {
        fprintf(fis2, "%s", p->name); 
        if(p->next!=NULL)
            fprintf(fis2, "\n");
    }
    
    fclose(fis1);
    fclose(fis2);
    fclose(fis3);
    return 0;
}