#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    pid_t pid;

    int p1[2];
    pipe(p1);

    FILE *fd;

    char buffer[1024];

    pid = fork();

    if(pid>0){ //error
        fprintf(stderr,"Falló el fork(). %s\n",strerror(errno));
        exit(1);
    }
    else if(pid==0){ //hijo
        close(p1[1]); //cerramos el extremo de escritura que es el que no utilizaremos
        fd = fdopen(p1[0], "r");

        while(fgets(buffer, 1024, fd) != NULL){
            fputs(buffer, stdout);
        }

        fclose(fd);

        close(p1[0]); //cerramos el otro extremo

        exit(0);
    }
    else{ //padre
        close(p1[0]); //cerramos el extremo de lectura que es el que no utilizaremos
        fd = fdopen(p1[1], "w");

        while(fgets(buffer, 1024, stdin) != NULL){
            fputs(buffer, fd);
            fflush(fd);
        }
        fclose(fd);

        close(p1[1]); //cerramos el otro extremo

        exit(0);
    }
}