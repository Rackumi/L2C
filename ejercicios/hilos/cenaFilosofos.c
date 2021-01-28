#include <thread_db.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define FILOSOFOS 5

int estado_filosofos[FILOSOFOS];
pthread_mutex_t palillo[FILOSOFOS];

void *filosofo(void *num){
    int fil_id = *(int *)num;

    while(1){
        estado_filosofos[fil_id] = 0;
        printf("Filosofo %d pensando\n", fil_id);
        sleep((rand()%2 +1));

        estado_filosofos[fil_id] = 1;
        printf("quiere comer");

    }
}

int main(void){

    thread_t th;
    int i;
    int fil_ids[FILOSOFOS];

    for(i=0; i<FILOSOFOS; i++){
        fil_ids[i] = i;
        pthread_create(&th, NULL, filosofo, (void*)&fil_ids[i]);
    }

}