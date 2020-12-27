#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

int pid;

void fManejador(int sig){
    if(pid == 0){
        printf("Hijo: Recibida la señal %d\n", sig);
        kill(getpid(), SIGUSR1); // le mando a mi padre la señal sigusr1(segunda)
        exit(0);
    }
    else{
        printf("Padre: Recibida la señal %d\n", sig); // el padre se mete por aqui
    }
}

int main(){

    signal(SIGUSR1, fManejador); //cuando este proceso reciba sigusr1 saltara la funcion manejador

    pid = fork(); //ahora tenemos dos procesos, ambos con el manejador
    if(pid == 0){
        while(1); //espera activa (pause() es espera pasiva)
        // cuando este hijo proceso reciba la primera señal de la linea 30 activará el manejador
    }
    else{
        kill(pid, SIGUSR1); //le manda al hijo la señal sigusr1(primera)
        wait(NULL); //y se bloquea esperando al hijo
        //recibe la segunda señal de la lunea 12 y deja de estar bloqueado y salta la funcion manejador
        //vuelve al w8 hasta que el hijo acabe, el cual entraria ahora por exit y el padre tmb finalizaria
        printf("El hijo ha terminado");
    }

    return 0;

}
