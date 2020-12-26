#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    int i;
    int first, last, increment;

    if(argc == 2){
        first = 1;
        increment = 1;
        last = atoi(argv[1]);
    }
    else if(argc == 3){
        first = atoi(argv[1]);
        increment = 1;
        last = atoi(argv[2]);
    }
    else if(argc == 4){
        first = atoi(argv[1]);
        increment = atoi(argv[2]);
        last = atoi(argv[3]);
    }
    else{
        fprintf(stderr,"Uso: %s. Numero de parametros erroreo\n", argv[0]);
        return 1;
    }
    for(i=first; i<=last; i=i+increment){
        printf("%d\n",i);
    }
    return 0;
}