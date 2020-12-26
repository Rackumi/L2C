#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    if(argc <= 1){
        fprintf(stderr,"Uso: %s. Numero de parametros erroreo\n", argv[0]);
        return 1;
    }

    char **inv1;
    int i, j;

    inv1 = malloc(1024*sizeof(char*));
    j=0;

    for(i=argc-1; i>=1; i--){
        inv1[j] = argv[i];
        j++;
    }

    for(i=0; i<argc-1; i++){
        for(j=strlen(inv1[i]); j>= 0; j--){
            printf("%c",inv1[i][j]);
        }
        printf(" ");
    }
    printf("\n");

    return 0;
}