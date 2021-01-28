#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

volatile int j = 0;
sem_t sem;

void *funct(){
    int i;
    for(i = 0; i<10000; i++){
        sem_wait(&sem);
        j = j + 1;
        sem_post(&sem);
    }
    pthread_exit(0);
}

int main(int argc, char** argv){
    pthread_t th1, th2;

    sem_init(&sem, 0, 1);

    pthread_create(&th1, NULL, funct, NULL);
    pthread_create(&th2, NULL, funct, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&sem);

    printf("j = %d\n", j);

    return 0;
}