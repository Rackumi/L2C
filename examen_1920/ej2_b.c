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

    FILE *p_p, *f_p, *f_e, *f_d;

    pipe(p);

    if(argc != 4){
        printf("Uso: %s programa argumentos\n", argv[0]);
        return(1);
    }

    for(int i=1; i<501; i++){
        f_pedidos[i] = 0;
        f_existencias[i] = 0;
    }

    pid = fork();
    if(pid < 0){
        fprintf(stderr,"Falló el fork().\n%s\n",strerror(errno));
        exit(1);
    }else if(pid == 0){ //Hijo
        close(p[1]);
        int continuar = 0;
        p_p = fdopen(p[0], "r");
        while( continuar > -2){
            if(fgets(buf, 1024, p_p)!= NULL){
                if(atoi(buf) == -1){
                    continuar--;
                }else{
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
                    }else{
                        f_pedidos[codigo] = f_pedidos[codigo] + cantidad;
                    }
                }
            }
        }
        f_d = fopen(argv[3],"w");
        if(f_d == NULL){
            fprintf(stderr,"Falló el archivo guardar existencias.\n%s\n", strerror(errno));
            exit(1);
        }
        for(int j=1; j<501; j++){
            if(f_pedidos[j] > 0){
                int num = f_existencias[j] - f_pedidos[j];
                if(num < 10){
                    if(num < 0){
                        num = num*(-1) + 10;
                    }else{
                        num = 10 - num;
                    }
                    printf("Del producto %d hay que fabricar %d.\n",j,num);
                    sprintf(buf,"%d 10\n", j);
                }else{
                    sprintf(buf,"%d %d\n", j, num);
                }
                fputs(buf, f_d);
                fflush(f_d);
            }else if(f_existencias[j] > 0){
                sprintf(buf,"%d %d\n", j, f_existencias[j]);
                fputs(buf, f_d);
                fflush(f_d);
            }
        }
        fclose(f_d);
        exit(0);
    }else{ //Padre
        close(p[0]); //Cierro lectura
        f_e = fopen(argv[1],"r");
        if(f_e == NULL){
            fprintf(stderr,"Falló el archivo existencias.\n%s\n", strerror(errno));
            exit(1);
        }
        p_p = fdopen(p[1], "w");
        while(fgets(buf, 1024, f_e) != NULL){
            fputs(buf, p_p);
            fflush(p_p);
        }
        fputs("\n-1\n", p_p);
        fflush(p_p);
        fclose(f_e); //Cierro dirección archivo

        f_p = fopen(argv[2],"r");
        if(f_p == NULL){
            fprintf(stderr,"Falló el archivo existencias.\n%s\n", strerror(errno));
            exit(1);
        }
        while(fgets(buf, 1024, f_p) != NULL){
            fputs(buf, p_p);
            fflush(p_p);
        }
        fputs("\n-1\n", p_p);
        fflush(p_p);
        fclose(f_p);

        wait(NULL);
        exit(0);
    }
}