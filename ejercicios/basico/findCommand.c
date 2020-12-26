#include <stdio.h>
#include <string.h>
#include <unistd.h>

char* cmd2path(char* cmd){

    char buffer[1024];
    char* str;
    char* tokens;

//    if(strchr(cmd, '/')){
//        if(!access(cmd, X_OK)){
//            return strdup(cmd);
//        }
//        else{
//            return NULL;
//        }
//    }
//
//    str = getenv("PATH");
//    if(!str){
//        str = "/bin:/usr/bin";
//    }

    tokens = strtok(str,":");
    while (tokens != NULL){
        printf("%s %s\n",tokens, str);
        tokens = strtok(NULL, ":");
        if(tokens != NULL){
            strcpy(buffer, tokens);
            strcat(buffer, "/");
            strcat(buffer, cmd);

            if(!access(buffer,X_OK)){
                return strdup(buffer);
            }
        }
    }
    return NULL;
}

int main(int argc, char** argv){

    char *ruta;

    if (argc != 2) { //comprobamos que el numero de parametros sea correcto
        printf("Numero de argumentos erroneo\n");
        return -1;
    }

    ruta = cmd2path(argv[1]);
    if(ruta == NULL){
        printf("Error");
    }
    else{
        printf("$s esta en %s\n", argv[1], ruta);
    }

    return 0;

}