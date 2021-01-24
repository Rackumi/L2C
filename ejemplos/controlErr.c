#include <bits/types/FILE.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
    FILE *f1;
    f1 = fopen("file.txt", "r+");
    if(f1 == NULL){
        fprintf(stderr, "Error al abrir el fichero. %s\n", strerror(errno));
    }
    else{
        fprintf(f1,"todo gucci");
    }
    return 0;
}