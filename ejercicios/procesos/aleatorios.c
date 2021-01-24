#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int tuberia[2];
pid_t pid;

void fManejador(int sig){
    int r;

    if(pid == 0){
        r = rand() % 10;
        exit(0);
    }
}

int main(){

    pipe(tuberia);

    signal(SIGUSR1, fManejador);

    pid = fork();
    if(pid < 0){
        fprintf(stderr, "El fork ha fallado\n");
        exit(1);
    }
    else if(pid == 0){ //hijo
        close(tuberia[1]);
//        write(tuberia[1],buffer);
        close(tuberia[0]);
    }
    else{ //padre
        close(tuberia[0]);
        kill(pid, SIGUSR1);


        close(tuberia[1]);
    }

    return 0;

}