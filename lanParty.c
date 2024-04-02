#include <stdio.h>
#include <stdlib.h>
#define N 100 //definesc lungimea maxima a liniei dintr-un fisier intrare

int main(int argc, char *argv[])
{
    FILE *fis1, *fis2;
    char line[N];
    fis1 = fopen("date/t1/d.in", "r");
    if(fis1 == NULL)
    {
        printf("Fisierul nu poate fi deschis pentru citire\n");
        exit(1);
    }
    fis2 = fopen("out/r.out", "w");
    if(fis2 == NULL)
    {
        printf("Fisierul nu poate fi deschis pentru scriere\n");
        exit(1);
    }
    while(fgets(line, sizeof(line), fis1)!=NULL){
        fputs(line, fis2);
    }
    fclose(fis1);
    fclose(fis2);
    return 0;
}
