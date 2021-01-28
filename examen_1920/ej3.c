#include <stdio.h>
#include <thread_db.h>
#include <stdlib.h>

int repartidores[20];
int sedes[5];

pthread_mutex_t mutex;

void *fSedes(){
    int s = (rand() % 5);


}

int main(void){

    thread_t th;

//    mutex

    pthread_create(&th, NULL, fSedes, NULL);

    return 0;
}