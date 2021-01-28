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
        printf("El filosofo %d esta pensando\n", fil_id);

        sleep(rand() % 2 + 1);

        estado_filosofos[fil_id] = 1;
        printf("El filosofo %d tiene hambre\n", fil_id);

        //XXXXXXXXX seccion critica XXXXXXXXXXX

        if((fil_id % 2) == 0){ //si el colega es par
            pthread_mutex_lock(&palillo[fil_id%FILOSOFOS]);
            pthread_mutex_lock(&palillo[fil_id+1%FILOSOFOS]);
        }
        else{
            pthread_mutex_lock(&palillo[fil_id+1%FILOSOFOS]);
            pthread_mutex_lock(&palillo[fil_id%FILOSOFOS]);
        }

        estado_filosofos[fil_id] = 2; //esta lleno
        printf("El filosofo %d comiendo\n",fil_id);

        sleep(rand() % 2 + 1);

        //todos los filosofos devuelven el palillo al reves de como lo cogieron

        if((fil_id % 2) == 0){ //si el colega es par
            pthread_mutex_unlock(&palillo[fil_id+1%FILOSOFOS]);
            pthread_mutex_unlock(&palillo[fil_id%FILOSOFOS]);
        }
        else{
            pthread_mutex_unlock(&palillo[fil_id%FILOSOFOS]);
            pthread_mutex_unlock(&palillo[fil_id+1%FILOSOFOS]);
        }

        //XXXXXXXXX fin seccion critica XXXXXXXXXXX

    }
}

int main(void){

    pthread_t th;
    int i;
    int fil_ids[FILOSOFOS];

    for(i=0; i<FILOSOFOS; i++){
        fil_ids[i] = i;
        pthread_mutex_init(&palillo[i], NULL);
        pthread_create(&th, NULL, filosofo, (void*)&fil_ids[i]);
    }

    while(1);

}