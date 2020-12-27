#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(){

    int status;

    pid_t pid; //tipo de dato que actuar como un int, pero es especificos para pids
    pid = fork(); //desde esta linea de código ahora habrá 2 procesos que ejecutarán el mismo codigo

    if(pid<0){ //Error
        fprintf(stderr, "El fork ha fallado\n");
        exit(-1);
    }
    else if(pid == 0){ //proceso hijo
        printf("Soy el hijo\n");
        execlp("ls","ls","-la",NULL);
        fprintf(stderr,"Se ha producido un error en el execlp\n");
        exit(1); //se no falla no debería llegar aqui ya que no regresa en caso de exito
    }
    else{ //proceso padre
        wait(&status); //status ahora tendrá el valor de retorno del proceso hijo, que al haber llamado a ls
                       //devolverá 0 si ha acabado correctamente
        printf("El hijo ha terminado\n");
        exit(0);
    }

}