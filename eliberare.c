#include "functii.h"

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

void deleteQueue(Queue *q){
    Match *aux;
    while(!isEmptyQ(q)){
        aux = q->front;
        q->front = q->front->next;
        free(aux);
    }
    free(q);
}

void freeAVL(AVLNode *Root){
    if(Root == NULL)
        return;
    freeAVL(Root->left);
    freeAVL(Root->right);

    free(Root->TeamName);

    free(Root);
}

void freeBST(ANode *root)
{
    if(root == NULL)
        return;
    freeBST(root->left);
    freeBST(root->right);

    free(root->TeamName);

    free(root);
}

void freePrimele8(SNode *primele8)
{
    SNode *current = primele8;
    SNode *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current->TeamName);
        free(current);

        current = nextNode;
    }
}