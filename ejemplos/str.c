#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){

    // Hay tres forma de declarar strings (la ultima va regular)

    char str1[] = "Hola1";
    char *str2 = "Hola2";
//    char *str3 = (char *) ('H', 'o', 'l', 'a', '3', '\0');

    printf("%s\n",str1);
    printf("%s\n",str2);
//    printf("%s",str3);

    // Operaciones de los strings (string.h)

    // length
    int len = (int)strlen(str1); //hace falta castearlo
    printf("%d\n",len);

    // concat
    char str4[1024] = "Hola4"; // para concatenar el string origen debe ser lo suficientemente grande para que no pete al concatenar
    strcat(str4, str1);
    printf("%s\n", str4);

    // copy
    char scop[1024]; //una vez mas el destino debe tener suficiente espacio para no petar
    strcpy(scop,str2);
    printf("%s\n",scop);

    // duplicar
    char *dp = strdup(str1);
    printf("%s\n",dp);

    //strcpy vs strdup: el copy crea un puntero que acaba apuntando al mismo elemento,
    //mientras que el dup lo que hace es duplicar y crear otro objeto

    // buscar
    char *searchStr = strchr(str1, 'o');
    printf("%s\n",searchStr);
    // crea otro string desde donde ha puesto el char, esto daria => ola1

    //strcmp para comparar dos strings
    int result = strcmp(str1,str1);
    printf("%d\n",result);
    //devuelve 0 si son iguales, y -1(!=0) si son distintos

    return 0;
}