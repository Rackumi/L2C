#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define LONGBUFFER 256

int main(){
    int fde, fds, nr;
    char *entrada = "entrada";
    char *salida = "salida";
    char buffer[LONGBUFFER];

    if((fde=open(entrada,O_RDONLY)) == -1){
        printf("Error al abrir el fichero %s\n",entrada);
        return 1;
    }
    else if((fds=open(salida,O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1){
        printf("Error al abrir el fichero %s\n",salida);
        close(fde);
        return 1;
    }

    while((nr = read(fde,buffer,LONGBUFFER)) > 0){
        write(fds, buffer, nr);
    }

    close(fde);
    close(fds);
    return 0;
}