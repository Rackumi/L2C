#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int main(){
    pid_t pid;
    pid = fork();

    if(pid<0){ //Error

    }
    else if(pid==0){ //Proceso hijo
//        execvp()
    }
    else{ //Proceso padre
        wait(NULL);
    }

    return 0;
}