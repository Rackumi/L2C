#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(){

    pid_t pid; //tipo de dato que actuar como un int, pero es especificos para pids
    pid = fork(); //desde esta linea de código ahora habrá 2 procesos que ejecutarán el mismo codigo

    if(pid<0){ //Error
        fprintf(stderr, "El fork ha fallado");
        exit(-1);
    }
    else if(pid == 0){ //proceso hijo
        printf("Soy el hijo\n");
        sleep(10);
        exit(0);
    }
    else{ //proceso padre
        waitpid(pid, NULL, 0); //es bloqueante
        printf("El hijo ha terminado\n");
    }

    return 0; //hacer un return de la funcion main es hacer un exit

}