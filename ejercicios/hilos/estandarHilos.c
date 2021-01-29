#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

int personas[N];

pthread_mutex_t mutex;
pthread_cond_t condiciones[N];

void *func(void *num){

    int id = *(int *)num;
    while(1){
        //hacer una primera acciones con un random para que se descuadren los hilos, se suele utilizar sleep() y rand()
        //puede que ni haga falta hacerlo

        //Entramos a la primera seccion critca (ENTRADA)
        pthread_mutex_lock(&mutex); //aqui dentro solo puede haber un hilo a la vez
        //if(cumple condicion)
            pthread_cond_wait(&condiciones[id], &mutex);

        //hacemos lo que se suponga que tenemos que hacer dentro de la seccion critica de entrada
        pthread_mutex_unlock(&mutex);
        //sales de la primera seccion critica

        /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

        //aqui ahora suele haber otra variable aleatoria que ya sea un sleep con un rand o algo del palo
        sleep(rand()%2+1);

        /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

        //Entramos a la segunda seccion critica (SALIDA)
        pthread_mutex_lock(&mutex); //aqui dentro solo puede haber un hilo a la vez
        //if(cumple condicion)
        pthread_cond_signal(&condiciones[id]);

        //hacemos lo que se suponga que tenemos que hacer dentro de la seccion critica de salida
        pthread_mutex_unlock(&mutex);
        //sales de la segunda seccion critica

    }

}

int main(int argc, char **argv){
    pthread_t t;
    int i;

    pthread_mutex_init(&mutex,NULL);
    for(i=0; i<N; i++){
        personas[i] = i; //asignamos el identificador
        pthread_cond_init(&condiciones[i], NULL);
        pthread_create(&t, NULL, func,(void*)&personas[i]);
    }

    while(1); //para que el programa no acabe hasta que no mande ctrl+c

}