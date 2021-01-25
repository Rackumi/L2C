#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

int p1[2];
pid_t pid;

void fManejador(int sig){
    int r;
    if(pid == 0){
        r = rand() % 11;
        write(p1[1], &r, 1024);
        exit(0);
    }
}

int main(){

    int r;
    pipe(p1);
    char buffer[1024];
    signal(SIGUSR1, fManejador);

    pid = fork();
    if(pid < 0){
        fprintf(stderr, "El fork ha fallado\n");
        exit(1);
    }
    else if(pid == 0){ //hijo
        close(p1[0]);
        while(1);
    }
    else{ //padre
        close(p1[1]);
        while(fgets(buffer, 1024, stdin) != NULL){
            kill(pid, SIGUSR1);
            read(p1[0], &r, 1024);
            printf("%d\n",r);
        }

        close(p1[1]);

        kill(pid, SIGKILL);
        wait(NULL);
        exit(0);
    }

    return 0;

}