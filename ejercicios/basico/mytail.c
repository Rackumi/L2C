#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

    int n, x, j;
    int i;
    char buf[1024];
    char **aux;

    if(argc == 1){
        n = 10;
    }
    else if(argc == 2){
        char* num = argv[1] + 1;
        n = atoi(num);
    }
    else{
        fprintf(stderr,"Uso: %s. Numero de parametros erroreo\n", argv[0]);
        return 1;
    }

    i=0;
    aux = malloc(1024*sizeof(char));
    while(fgets(buf, 1024, stdin) != NULL){
        aux[i] = strndup(buf,1024); //para que al final del bucle aux no contenga el último elem en todas las posiciones
        i++;
    }

    if(i<n){ //si el numero de lineas es menor que n, entonces imprimimos all
        for(j=0; j<i; j++){
            printf("%s", aux[j]);
        }
    }
    else{ //sino habrá que imprimir solo las n ultimas
        x = i - n;
        for(j=x; j<i; j++){
            printf("%s", aux[j]);
        }

    }

    return 0;
}