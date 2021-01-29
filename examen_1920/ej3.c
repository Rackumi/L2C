#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define REPARTIDORESS 20
#define SEDESS 5

int *sedes;

int *repartidores_id;

int aux, aux2, nPaquetes, j;

pthread_mutex_t mutex;

pthread_cond_t cond1;

void *repartidor(void *n){
    //tendremos dos secciones criticas, la primera cuando cogemos paquetes y la segunda cuando los dejamos
    //esto se debe a que no queremos que se produzca una condcion de carrera. Esto sucederia si se pudiese acceder a una variable a la vez desde dos hilos
    //distintos, lo que haria que el valor de esta variable no fuese el real
    pthread_mutex_lock(&mutex); //inicio seccion critica 1
    aux = rand()%5; //selecciona una de las 5 sedes aleatoriamente
    while(sedes[aux] == 0){
        pthread_cond_wait(&cond1, &mutex);
    }
    printf("el repartidor, %d va la sede %d y coge sus paquetes\n",repartidores_id[(int)n], aux);
    nPaquetes = sedes[aux];
    sedes[aux] = 0;
    pthread_mutex_unlock(&mutex); //fin seccion critica 1

    sleep((rand()%2));

    pthread_mutex_lock(&mutex); //inicio seccion critica 2
    aux = rand()%5; //selecciona una de las 5 sedes aleatoriamente
    while(sedes[aux] > 20){
        pthread_cond_signal(&cond1);
    }
    printf("el repartidor, %d va la sede %d y deja sus paquetes\n",repartidores_id[(int)n], aux);
    sedes[aux] = nPaquetes;

    for(j=0; j<aux; j++){  //reparte los paquetes que tiene a otras sedes
        aux2 = rand()%5;
        sedes[aux2]++; //aumentan en 1 el paquete en una sede aleatoria
        sedes[aux]--; //decrementa en 1 el paquete en la sede en la que estamos
    }

    pthread_mutex_unlock(&mutex); //fin seccion critica 2


}

int main(void) {
    int i;
    sedes = malloc(sizeof(int)*SEDESS);

    for(i=0; i<SEDESS; i++){
        sedes[i] = 15;
    }

    pthread_t th; //creamos el thread

    pthread_cond_init(&cond1, NULL);

    for(i=0; i<REPARTIDORESS; i++){
        repartidores_id[i] = i;
        pthread_create(&th,NULL,repartidor,(void*)&repartidores_id);
    }

    while(1); //no acaba hasta que nosotros lo decidamos
}