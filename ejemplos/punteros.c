#include <stdio.h>
#include <stdlib.h>

void sumar(int *a, int *b){
    *a = *a + *b;
}

int main(int argc, char** argv){

    int *pInt;
    int a = 10;
    pInt = &a; //referencia, el puntero apunta a "a"
    *pInt = 20; //accedemos al valor del puntero y lo modificamos

    printf("%d\n",a);
    //"a" tmb habrá cambiado

    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

    float* b1;
    int* b2;

    b1 = (float*)malloc(24*sizeof(float));
    b1[0] = 10;
//    b1++; // si avanzas con el puntero b1[0] sera a la posicion a la que hayas avanzado
    b1[1] = 20;
    printf("%.2f\n",b1[0]);
    printf("%.2f\n",b1[1]);

    b2 = calloc(16,sizeof(int)); // es como el malloc pero se inicializa a cero

    float *temp_a = realloc(b1, 48*sizeof(float )); //redimensiona
    b1 = temp_a;

    free(temp_a); // libera memoria
    //free(b1); //se liberamos b1 daria error xq ya hemos liberado temp_a y ambos apuntan al mismo lugar y esa zona ya esta liberada
    free(b2);

    //cabe recordar que el paso de argumentos por referencia se hace con punteros, por defecto se hace por valor
    int x = 100;
    int y = 133;
    sumar(&x,&y);

    printf("%d\n",x);

}