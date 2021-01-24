#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv){

    int fd1, fd2;

    char* buff = "hola";
    if ((fd1 = open(buff, O_RDONLY)) < 0){
        printf("Error al abrir el fichero %s, %s\n",buff, strerror(errno));
    }

//    if (line->redirect_input != NULL) { // <
//        fd = open(line->redirect_input, O_RDONLY); //abrimos el fichero
//        if (fd != -1) {
//            dup2(fd, 0); //redirigimos la entrada
//            close(fd); //cerramos el fd
//        } else {
//            fprintf(stderr, "Fichero: Error al abrir el fichero\n");
//            exit(-1);
//        }
//    }
//    if (line->redirect_output != NULL) { // >
//        fd = creat(line->redirect_output, 0666); //creamos el fichero
//        if (fd !=
//            -1) {                                   // permisos del mode 0666: R y W para user group y other
//            dup2(fd, 1); //redirigimos la salida
//            close(fd); //cerramos el fd
//        } else {
//            fprintf(stderr, "Fichero: Error al crear el fichero\n");
//            exit(-1);
//        }
//    }
//    if (line->redirect_error != NULL) { // >&
//        fd = open(line->redirect_error, 0666); //creamos el fichero
//        if (fd !=
//            -1) {                                   // permisos del mode 0666: R y W para user group y other
//            dup2(fd, 2); //redirigimos el error
//            close(fd); //cerramos el fd
//        } else {
//            fprintf(stderr, "Fichero: Error al crear el fichero\n");
//            exit(-1);
//        }
//    }

}