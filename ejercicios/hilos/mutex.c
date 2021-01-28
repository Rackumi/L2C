#include <pthread.h>
#include <stdio.h>

#define LONGITUD 10000
int buffer[LONGITUD];

pthread_mutex_t mutex; //mutex para sincronizar el acceso al buffer

void *func(void *param){
    int i;
    int elemDistinto = 0;

    while(1){ //bucle infinito
        pthread_mutex_lock(&mutex);

        for(i=1; i<LONGITUD; i++){
            if (buffer[0] != buffer[i]){
                elemDistinto = 1;
                break;
            }
        }

        if(elemDistinto)
            printf("Hijo: Error. Elementos de buffer distintos\n");
        else
            printf("Hijo: Corrector\n");

        elemDistinto = 0;

        pthread_mutex_unlock(&mutex);

    }

}

int main(int argc, char **argv){
    int i, contador;
    contador = 0;

    pthread_t t1; //tid del hilo

    pthread_mutex_init(&mutex, NULL); //inicializamos el mutex

    int errNum = pthread_create(&t1, NULL, func, NULL); //metemos el thread por la fucion y ponemos errNum para ver si hay error

    if(errNum != 0){//por si da error
        fprintf(stderr, "Error al crear el hilo"); //perror("No se pudo craer el thread");
        return 1;
    }

    while(1){ //bucle infinito
        pthread_mutex_lock(&mutex);

        for(i=0; i<LONGITUD; i++){
            buffer[i] = contador;
        }

        pthread_mutex_unlock(&mutex);

        contador++;
    }

}