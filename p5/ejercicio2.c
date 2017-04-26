#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
struct nodo {
    pthread_t hilo;
    struct nodo *next;
};
struct contenedor {
    char *origen;
    char *destino;
    char *ruta;
    struct nodo *next;
};
void *lectura_archivos(void *arg);

int main(int argc, char const* argv[]) {
    struct contenedor *cont = malloc(sizeof(struct contenedor));
    char *origen = "prueba/";
    cont->origen = origen;
    cont->ruta="";
    cont->destino = "dest/";
    pthread_t hilo;
    pthread_create(&hilo, NULL, lectura_archivos, (void*)cont);
    pthread_join(hilo, NULL);
    return 0;
}

void *lectura_archivos(void *arg) {
    struct contenedor *super = arg;
    DIR *directorio;
    struct dirent *archivo;
    struct stat datos_archivo;
    char nana[100];
    char *origen = super->origen;
    strcpy(nana, origen);
    strcat(nana, super->ruta);
    directorio = opendir(nana);
    printf("Nana es %s Origen es %s\n", nana, origen);
    int i = 0;
    while ((archivo = readdir(directorio)) != NULL) {
        if (strcmp(archivo->d_name, ".") && strcmp(archivo->d_name, "..")) {
            strcpy(nana, origen);
            strcat(nana, super->ruta);
            if (stat(strcat(nana, archivo->d_name), &datos_archivo) == 0){
                printf("El archivo es %s ", archivo->d_name);
                if (S_ISDIR(datos_archivo.st_mode)){
                    printf("Es un directorio - ");
                    pthread_t hilo;
                    char nuevo[100];
                    char copia[100];
                    strcpy(nuevo, super->ruta);
                    strcat(nuevo, archivo->d_name);
                    strcat(nuevo, "/");
                    struct contenedor *siguiente = malloc(sizeof(struct contenedor));
                    siguiente->origen = super->origen;
                    siguiente->ruta= nuevo;
                    siguiente->destino = super->destino;
                    printf("Proximo direcctorio %s\n", nuevo);
                    strcpy(copia, super->destino);
                    strcat(copia, nuevo);
                    mkdir(copia, 0777);
                    pthread_create(&hilo, NULL, lectura_archivos, (void*)siguiente);
                    pthread_join(hilo, NULL);
                } else {
                    //copiar archivos
                    char super_archivo[100];
                    char ruta_vieja[100];
                    char buffer[1];
                    strcpy(super_archivo, super->destino);
                    strcpy(ruta_vieja, super->origen);
                    strcat(super_archivo, super->ruta);
                    strcat(ruta_vieja, super->ruta);
                    strcat(super_archivo, archivo->d_name);
                    strcat(ruta_vieja, archivo->d_name);
                    printf("La ruta para copiar es %s y la ruta vieja es: %s\n", super_archivo, ruta_vieja);
                    int archivo_abierto = open(ruta_vieja, O_RDONLY);
                    int archivo_clon = open(super_archivo, O_WRONLY | O_CREAT, 0640);
                    while (0 < read(archivo_abierto, buffer, 1))
                        write(archivo_clon, buffer, 1);

                    close(archivo_abierto);
                    close(archivo_clon);
                }
                printf("\n");
            }
        }
        i++;
    }
    return 0;
}
