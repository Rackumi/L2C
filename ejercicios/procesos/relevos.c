#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

int pids[4];
pid_t pid;
int i;

void manejador(int sig){
    printf("Soy el hijo %d con el pid %d\n",i,pids[i]);
    sleep(1);
    if(i != 0){
        printf("terminé, paso el testigo al hijo %d con pid %d\n",i-1,pids[i-1]);
        kill(pids[i-1], SIGUSR1);
    }
    else{
        printf("terminé\n");
    }
    exit(0);

}

int main(){

    for(i=0; i<4; i++) {
        pid = fork();
        signal(SIGUSR1, manejador);
        if (pid < 0) {
            fprintf(stderr, "Error al hacer el fork, proceso no creado. %s\n", strerror(errno));
            exit(1);
        } else if (pid == 0) {// hijo
            pause();
        } else {//padre
            pids[i] = pid;
        }
    }

    kill(pids[3], SIGUSR1);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Todos los hijos terminaron");

    return 0;
}