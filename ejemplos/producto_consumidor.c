#include <sys/types.h>
#include <pthread.h>
#define BUFF_SIZE 1024
#define TOTAL_DATOS 100000

int n_datos;
int buffer[BUFF_SIZE];

pthread_mutex_t mutex;
pthread_cond_t no_lleno, no_vacio;

void *productor(){
    int i, dato;
    for(i=0; i<TOTAL_DATOS; i++){
        pthread_mutex_lock(&mutex);
        while (n_datos == BUFF_SIZE) {
            pthread_cond_wait(&no_lleno, &mutex);
        }
        buffer[i % BUFF_SIZE] = dato;
        n_datos++;
        pthread_cond_signal(&no_vacio);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


void *consumidor(){
    int i, dato;
    for(i=0; i<TOTAL_DATOS; i++){
        pthread_mutex_lock(&mutex);
        while (n_datos == 0){
            pthread_cond_wait(&no_vacio, &mutex);
        }
        dato = buffer[i % BUFF_SIZE];
        n_datos--;
        pthread_cond_signal(&no_lleno);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv){
    pthread_t t1, t2;

    pthread_cond_init(&no_lleno, NULL);
    pthread_cond_init(&no_vacio, NULL);

    pthread_create(&t1, NULL, productor, NULL);
    pthread_create(&t2, NULL, consumidor, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&no_lleno);
    pthread_cond_destroy(&no_vacio);

    return 0;
}