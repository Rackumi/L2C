#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;

void *f1(void *arg){
    printf("Soy el t1\n");

    sem_wait(&sem);
    printf("Este mensaje se deberia mostrar segundo\n");

    pthread_exit(0);
}

void *f2(void *arg){
    printf("Soy el t2\n");

    printf("Este mensaje se deberia mostrar primero\n");
    sem_post(&sem);

    pthread_exit(0);
}

int main(){

    pthread_t th1, th2; //creas los dos threads
    sem_init(&sem, 0, 0); //el segundo 0 significa el valor inicial del semaforo, el primero es para threads y distinto de 0 para procesos

    //hay 3 hilos en total

    pthread_create(&th1, NULL, f1, NULL); //primero aqui
    pthread_create(&th2, NULL, f2, NULL); //segundo aqui

    pthread_join(th1, NULL); //tercer hilo espera aqui, que es el principal
    pthread_join(th2, NULL); //estos join se hacen para que no se acabe el programa antes de acabar los threads

    sem_destroy(&sem);

    return 0;

}