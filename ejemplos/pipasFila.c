#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wait.h>

int main(int argc, char** argv){
    //aqui usaremos FILE* con el fdopen y luego utlizaremos fread, fwrite, fclose, fputs, fgets

    int p1[2];
    pipe(p1);

    FILE *fd;

    char buf[1024];
    pid_t pid;

    pid = fork();
    if(pid<0){ //error
        fprintf(stderr,"El fork ha fallado. %s", strerror(errno));
        exit(1);
    }
    else if(pid==0){ //hijo
        printf("soy el hijo\n"); //podriamos usar puts que escribe un mensaje a la stdout
        close(p1[1]); //cerramos la parte del pipe que no vamos a usar

        fd = fdopen(p1[0], "r"); // asignamos lectura
        fgets(buf, 1024, fd); //leemos y lo metemos en el buffer
        fclose(fd); //cerramos el fd

        close(p1[0]); //cerramos la otra parte del pipe

        printf("%s\n",buf);

        exit(0);
    }
    else{ //padre
        printf("soy el padre\n"); //el padre envia al hijo
        close(p1[0]); //cerramos la parte del pipe que no vamos a usar

        fd = fdopen(p1[1],"w"); //asignamos escritura
        fprintf(fd,"hola antonio"); //escribimos
        fflush(fd); //el flush
        fclose(fd); //cerramos el fd

        close(p1[1]); //cerramos la otra parte del pipe

        wait(NULL);
        exit(0);
    }
}