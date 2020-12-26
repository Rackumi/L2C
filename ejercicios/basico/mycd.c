#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*
    Realmente no funciona completamente, el directorio que cambia es el de programa no el de la shell
    si yo quiero que cambie el directorio quien tiene que hacer la llamada es la propia shell.
    Porque sino quien hace la llamada será el programa y cuando acabe dejara de estar en ese directorio.
    Esto es porque cd es una mandato interno.
*/

int main(int argc, char *argv[]){

    char *dir;
    char cwd[1024];

    if(argc == 1){
        dir = getenv("HOME");
        if (dir == NULL) {
            fprintf(stderr, "No existe la variable $HOME\n");
        }
    }
    else if(argc == 2){
        dir = argv[1];
    }
    else{
        fprintf(stderr,"Uso: %s. Numero de parametros erroreo\n", argv[0]);
        return 1;
    }

    if(chdir(dir) != 0){ //se comprobar si es un directorio y si no lo es sale un error
        fprintf(stderr, "cd: %s: No existe el archivo o el directorio. Error: %s\n", dir, strerror(errno));
    }
    else{
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd); //escribe la ruta absoluta del directorio actual
    }

    return 0;
}