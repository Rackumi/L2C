#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){
    pid_t pid;
    int f_pedidos[501]; //datos fichero pedidos
    int f_existencias[501]; // datos fichero existencias
    char buf[1024];

    int p[2];
    pipe(p);

    FILE *p_p, *f_p, *f_e;

    if(argc != 3){
        fprintf(stderr, "Numero de parametro erroneo. %s\n",strerror(errno));
        return 1;
    }

    for(int i=1; i<501; i++){ //inicializas all a 0
        f_pedidos[i] = 0;
        f_existencias[i] = 0;
    }

    pid = fork();
    if(pid<0){ //error
        fprintf(stderr,"Falló el fork().\n%s\n",strerror(errno));
        exit(1);
    }
    else if(pid==0){ //hijo
        close(p[1]); //cierro el extremo que no voy a usar
        int continuar = 0;
        p_p = fdopen(p[0], "r");

        // movidas del problema

        while( continuar > -2){
            if(fgets(buf, 1024, p_p)!= NULL){
                if(atoi(buf) == -1){
                    continuar--;
                }
                else{
                    int codigo;
                    int cantidad;
                    int j=0;
                    codigo = atoi(&buf[j]);
                    while(buf[j] != ' '){
                        j++;
                    }
                    cantidad = atoi(&buf[j]);
                    while(buf[j] != ' '){
                        j++;
                    }
                    if(continuar == 0){
                        f_existencias[codigo] = cantidad;
                    }
                    else{
                        f_pedidos[codigo] = f_pedidos[codigo] + cantidad;
                    }
                }
            }
        }
        for(int j=1; j<501; j++){
            if(f_pedidos[j] > 0){
                int num = f_existencias[j] - f_pedidos[j];
                if(num < 10){
                    if(num < 0){
                        num = num*(-1) + 10;
                    }
                    else{
                        num = 10 - num;
                    }
                    printf("Del producto %d hay que fabricar %d.\n",j,num);
                }
            }
        }

        // movidas del problema

        exit(0);
    }
    else{ //padre
        close(p[0]); //cierro el extremo que no voy a usar

        p_p = fdopen(p[1], "w"); //mandas por la pipe lo que te venga del fichero

        // XXXXXXXXXXXXXXXXXXXXXXXXX fichero 1 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

        f_e = fopen(argv[1],"r"); //abres el fichero del primer argumento
        if(f_e == NULL){
            fprintf(stderr,"Fallo al abrir el archivo existencias. %s\n", strerror(errno));
            exit(1);
        }

        while(fgets(buf, 1024, f_e) != NULL){
            fputs(buf, p_p);
            fflush(p_p);
        }
        fputs("-1", p_p); //le mandas un numero negativo para señalizar que ya paras
        fflush(p_p);
        fclose(f_e); //Cierro FILD del archivo

        // XXXXXXXXXXXXXXXXXXXXXXXXX fichero 2 (repito) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

        f_p = fopen(argv[2],"r"); //abres el fichero del segundo argumento
        if(f_p == NULL){
            fprintf(stderr,"Fallo al abrir el archivo existencias. %s\n", strerror(errno));
            exit(1);
        }
        while(fgets(buf, 1024, f_p) != NULL){
            fputs(buf, p_p);
            fflush(p_p);
        }
        fputs("-1", p_p);
        fflush(p_p);
        fclose(f_p);

        // XXXXXXXXXXXXXXXXXXXXXXXXX fin XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

        wait(NULL);
        close(p[1]);
        exit(0);
    }
}