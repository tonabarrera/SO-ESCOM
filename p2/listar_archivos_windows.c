#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct stat datos_archivo;
    DIR *direccion;
    struct dirent *archivo;
    char path_carpeta[250];

    printf("%s\n", "Listar archivos");
    printf("%s\n", "Que directorio quieres? (teclea '.' para el actual):");
    fgets (path_carpeta, 250, stdin);
    size_t salto = strlen(path_carpeta)-1;

    if (path_carpeta[salto] == '\n')
        path_carpeta[salto] = '\0';

    strcat(path_carpeta, "/");
    direccion = opendir(path_carpeta);
    printf("%s %s\n", "Mostrando archivos del directorio: ", path_carpeta);
    printf("Nombre\t\tTamano (Bytes) \t\t Ultimo accesso \t \n");
    
    while((archivo=readdir(direccion)) != NULL){
        if (strcmp(archivo->d_name, ".") && strcmp(archivo->d_name, "..") ){
            printf("%s\t", archivo->d_name);
            stat(strcat(path_carpeta, archivo->d_name), &datos_archivo);
            printf("%ld\t\t\t", datos_archivo.st_size);
            printf("%s \n", ctime(&datos_archivo.st_atime));
        }
    }
    return 0;
}