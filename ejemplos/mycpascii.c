#include <stdio.h>
#include <unistd.h>

#define LONGBUFFER2 1024

int main(int argc, char** argv){

    FILE  *fe, *fs;
    char *entrada = "entrada";
    char *salida = "salida";
    char buffer[LONGBUFFER2];

    if((fe=fopen(entrada,"r")) == NULL){
        fprintf(stderr,"Error al abrir el fichero %s\n",entrada);
        return 1;
    }
    else if((fs=fopen(salida,"w")) == NULL){
        fprintf(stderr,"Error al abrir el fichero %s\n",salida);
        fclose(fs);
        return 1;
    }

    while(fgets(buffer, LONGBUFFER2, fe) != NULL){
        fputs(buffer, fs);
    }

    fclose(fe);
    fclose(fs);
    return 0;
}