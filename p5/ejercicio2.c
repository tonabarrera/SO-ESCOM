#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
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
        //printf("Entro al while %i\n", i);
        if (strcmp(archivo->d_name, ".") && strcmp(archivo->d_name, "..")) {
            strcpy(nana, origen);
            strcat(nana, super->ruta);
            if (stat(strcat(nana, archivo->d_name), &datos_archivo) == 0){
                printf("El archivo es %s ", archivo->d_name);
                if (S_ISDIR(datos_archivo.st_mode)){
                    printf("Es un directorio - ");
                    pthread_t hilo;
                    char nuevo[100];
                    strcpy(nuevo, super->ruta);
                    strcat(nuevo, archivo->d_name);
                    strcat(nuevo, "/");
                    struct contenedor *siguiente = malloc(sizeof(struct contenedor));
                    siguiente->origen = super->origen;
                    siguiente->ruta= nuevo;
                    siguiente->destino = super->destino;
                    printf("Proximo direcctorio %s\n", nuevo);
                    pthread_create(&hilo, NULL, lectura_archivos, (void*)siguiente);
                    pthread_join(hilo, NULL);
                } else {
                    //copiar archivos
                }
                printf("\n");
            }
        }
        i++;
    }
    return 0;
}
