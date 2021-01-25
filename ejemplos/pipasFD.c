#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wait.h>

int main(int argc, char** argv){
    //aqui usaremos read, write y close para manipular los fd

    int p1[2];
    pipe(p1); //entrada p1[1] y salida p1[0]

    int pid;
    char buf[1024];

    pid = fork(); //el pipe se comunicara de padre a hijo
    if(pid<0){ //error
        fprintf(stderr,"El fork ha fallado. %s", strerror(errno));
        exit(1);
    }
    else if(pid==0){ //hijo
        printf("soy el hijo\n"); //podriamos usar puts que escribe un mensaje a la stdout

        close(p1[1]);
        read(p1[0], buf, 1024);
        printf("el hijo de dice que el padre dice: %s\n",buf);
        close(p1[0]);

        exit(0);
    }
    else{ //padre
        printf("soy el padre\n");

        close(p1[0]);
        write(p1[1], "holo", 5);
        close(p1[1]);
        wait(NULL);
        exit(0);
    }

}