#include <fcntl.h>
#include <unistd.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){

    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    FILE* fd1, *fd2;

    char buffer[1024];

    pid_t pid;

    pid = fork();
    if(pid<0){
        fprintf(stderr,"El fork ha fallado. %s", strerror(errno));
        exit(1);
    }
    else if(pid==0){ //hijo
        close(pipe1[1]);
        close(pipe2[0]);

        fd1 = fdopen(pipe1[0], "r");
        fd2 = fdopen(pipe2[1], "w");

        while(fgets(buffer, 1024, fd1) != NULL) {
            for(int i=0; i<strlen(buffer); i++){
                buffer[i] = toupper(buffer[i]);
            }
            fputs(buffer, fd2);
            fflush(fd2);
        }

        close(pipe1[0]);
        close(pipe2[1]);
    }
    else{ //padre
        close(pipe1[0]);
        close(pipe2[1]);

        fd1 = fdopen(pipe1[1], "w");
        fd2 = fdopen(pipe2[0], "r");

        while(fgets(buffer, 1024, stdin) != NULL){
            fputs(buffer, fd1);
            fflush(fd1);

//            wait(NULL); //si le metes el w8 se bloquea

            fgets(buffer,1024,fd2);
            fputs(buffer,stdout);
        }

        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}