#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ./lanParty c.in d.in out1.out
    FILE *fis1, *fis2;
    char *line; 
    fis1 = fopen(argv[2], "r");

    if(fis1 == NULL)
    {
        printf("Fisierul nu poate fi deschis pentru citire\n");
        exit(1);
    }
    fis2 = fopen(argv[3], "w");

    
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
