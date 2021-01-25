#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void manejador(int sig){
    printf("de locos\n");
}

int main(int argc, char** argv){

    //signal(SIGINT, manejador); //saltara el manejador
    //signal(SIGINT, SIG_DFL); //esto haria que se acabase el programa xq la accion por defecto de sigint es terminar el proceso sin decir nada
    signal(SIGINT, SIG_IGN); //esto lo ignoraria seguira pillado en el pause

    pause();

    printf("ya he acabado\n");
    return 0;

}