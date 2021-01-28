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

//int open(char *name, int flags [,mode_t mode])
//name del fichero, flags: O_RDONLY(solo lectura),O_WRONLY, O_RDWR, O_APPEND, O_CREAT(aqui meteriamos los modes), O_TRUNC. Se separan por |
//devuelve el fd o -1 en caso de error

//int creat(char *name, mode_t)
//el mode es S_I(R,W,X)(USR,GRP,OTH) -> S_IRUSR, S_IWOTH...
//devuelve el fd o -1 en caso de error. Similar a open con O_WRONLY | O_TRUNC | O_CREAT

//size_t read(int fd, void* buf, size_t n_bytes)
//fd del que se va a leer, buffer de 1024, numero de bytes que se quieren leer
//devuelve el n de bytes leidos o -1 en caso de error. Lee n_bytes como maximo excepto si el fichero es menor

//size_t write(int fd, void* buf, size_t n_bytes)
//fd donde se quiere escribir, buffer de 1024 que contiene los datos a ecribir del fichero, el numero de bytes que se va a escribir
//devuelve el n de bytes escritos o -1 en caso de error

//off_t lseek(int fd, off_t offset, int whence)
//fd, desplazamiento y tipo de desplaz de puntero(SEEK_SET, SEEK_CUR, SEEK_END)
//devuelve la nueva posicion del puntero o -1 en caso de error

//int close(int fd)
//fd que se quiere cerrar(hasta que no se cierra el so no hace cositas)
//devuelve 0 si all ha ido bien o -1 en caso de error

//int dup(int fd)
//fd que se quiere duplicar, devuelve del fd o -1 en caso de error
//crea una copia del fd devolviendo el mas bajo posible

//int dup2(int oldfd, int newfd) => dup2(fd,1) ahora el fichero datos.txt envia datos por stdout (?)
//oldfd que se quiere duplicar, newfd nuevo fd, devuelve del fd o -1 en caso de error
//hace que newfd sea una copia de oldfd, cerrando newfd si es necesario

//mkdir crea un directorio => int mkdir(char* name, mode_t mode);
//rmdir borra un dir => char* getcwd(char* buf, size_t size)
//getcwd obtiene pwd
//chdir es un cd => int chdir(char* name)

}