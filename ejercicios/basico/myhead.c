#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    int n, aux;
    char buff[1024]; //no debería haber lineas de mayor tamaño

    if(argc == 1){
        n = 10;
    }
    else if( argc == 2){
        n = atoi(argv[1]+1); //para el -
    }
    else{
        fprintf(stderr,"Uso: %s. Numero de parametros erroreo\n", argv[0]);
        return 1;
    }

    aux = 0;
    /*
    Aqui se hace comprobación perezosa, si la primera falla ya no hago la
    segunda, asi evitamos hacer ese fgets y no hacer una linea de más
    */
    while(aux < n && fgets(buff, 1024, stdin) != NULL){ //no debe hacerse con un for xq yo no se las lineas hasta que acabo
        printf("%s",buff);
        aux++;
    }

    return 0;

}