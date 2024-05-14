#include "LanParty.h"

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