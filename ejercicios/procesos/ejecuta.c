#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){

    pid_t pid;
    int status;

    if(argc < 2){
        fprintf(stderr,"Uso: %s. Numero de parametros erroreo\n", argv[0]);
        return 1;
    }

    pid = fork();
    if(pid<0){ //Error
        fprintf(stderr, "El fork ha fallado\n");
        exit(1);
    }
    else if(pid==0){ //Proceso hijo
        execvp(argv[1],argv+1); //+1 para no meter el nombre del programa
        //aqui no se deberia llegar a menos que el execvp de un error
        printf("Error al ejecutar este comando: %s\n", strerror(errno));
        exit(1);
    }
    else{ //Proceso padre
        wait(&status);
        /*
           status ahora tendra el estado de finalizacion del hijo y usamos las siguientes dos macros
           para saber si ha acabado correctamente (es una codificacion rara y por eso usamos macros)
           - WIFEXITED(statusHijo): es 0 si el hijo ha terminado de una manera anormal(caida, matado con un kill, etc).
           - WEXITSTATUS(statusHijo): devuelve el valor que ha pasado el hijo a la funcion exit(), siempre y cuando la
                                      macro anterior indique que la salida ha sido por llamada a exit().
        */
        if(WIFEXITED(status) != 0){ //distinto de 0 si hijo terminó
            if(WEXITSTATUS(status) != 0){ //si distinto de 0 el programa ejecutó bien
                printf("El comando se ejecutó correctamente\n");
            }
        }
        exit(0);
    }

    return 0;

}