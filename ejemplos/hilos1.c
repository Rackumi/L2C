#include <pthread.h>
#include <thread_db.h>
#include <stdio.h>

int sum = 0;

void *suma(void *num){
    int limite = *(int *) num;
    for(int i = 0; i<= limite; i++){
        sum += i;
    }
    pthread_exit(0);
}

int main(int argc, char** argv){

    thread_t t1;
    int n = 10;

    pthread_create(&t1, NULL, suma, (void *) &n);
    pthread_join(t1, NULL);
    printf("La suma de los primeros n numeros es = %d\n",sum);
    return 0;
}