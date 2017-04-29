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
    pthread_t *hilo;
    struct nodo *next;
};
struct contenedor {
    char *origen;
    char *destino;
    char *ruta;
};
void *lectura_archivos(void *);
int copiar_archivo(char *, char *, struct contenedor *, char *);

int main(int argc, char const* argv[]) {
    size_t salto;
    pthread_t hilo;
    struct contenedor *cont = malloc(sizeof(struct contenedor));
    cont->origen = malloc(sizeof(char)*20);
    cont->ruta = "";
    cont->destino = malloc(sizeof(char)*20);
    printf("%s\n", "Directorio origen:");
    fgets(cont->origen, 20, stdin);
    salto = strlen(cont->origen)-1;
    if (cont->origen[salto] == '\n')
        cont->origen[salto] = '\0';
    strcat(cont->origen, "/");
    printf("%s\n", "Directorio destino:");
    fgets(cont->destino, 20, stdin);
    salto = strlen(cont->destino)-1;
    if (cont->destino[salto] == '\n')
        cont->destino[salto] = '\0';
    strcat(cont->destino, "/");
    pthread_create(&hilo, NULL, lectura_archivos, (void*)cont);
    pthread_join(hilo, NULL);
    free(cont);
    return 0;
}

void *lectura_archivos(void *arg) {
    struct contenedor *contenido = arg;
    char *ruta = malloc(sizeof(contenido->ruta));
    pthread_t *hilo;
    char *nuevo;
    char *ruta_siguiente;
    char *ruta_anterior;
    struct contenedor *siguiente;
    strcpy(ruta, contenido->ruta);
    char *origen = contenido->origen;
    char *copia;
    DIR *directorio;
    struct dirent *archivo;
    struct stat datos_archivo;
    struct nodo *elemento = NULL;
    char *dir_src = malloc(sizeof(ruta) + sizeof(origen));
    char *archivo_dir;
    struct nodo *temporal;
    struct nodo *aux;
    strcpy(dir_src, origen);
    strcat(dir_src, ruta);
    directorio = opendir(dir_src);
    while ((archivo = readdir(directorio)) != NULL) {
        if (strcmp(archivo->d_name, ".") && strcmp(archivo->d_name, "..")) {
            archivo_dir = malloc(sizeof(dir_src) + sizeof(archivo->d_name));
            strcpy(archivo_dir, dir_src);
            if (stat(strcat(archivo_dir, archivo->d_name), &datos_archivo) == 0) {
                printf("\nEl elemento %s ", archivo->d_name);
                if (S_ISDIR(datos_archivo.st_mode)) {
                    printf("es un directorio y fue copiado");
                    hilo = malloc(sizeof(pthread_t));
                    nuevo = malloc(sizeof(ruta) + sizeof(archivo->d_name) + sizeof(char));
                    copia = malloc(sizeof(contenido->destino) + sizeof(nuevo));
                    strcpy(nuevo, ruta);
                    strcat(nuevo, archivo->d_name);
                    strcat(nuevo, "/");
                    siguiente = malloc(sizeof(struct contenedor));
                    siguiente->origen = contenido->origen;
                    siguiente->ruta = malloc(sizeof(nuevo));
                    strcpy(siguiente->ruta, nuevo);
                    siguiente->destino = contenido->destino;
                    strcpy(copia, contenido->destino);
                    strcat(copia, nuevo);
                    mkdir(copia, 0777);
                    temporal = malloc(sizeof(struct nodo));
                    temporal->next = NULL;
                    temporal->hilo = hilo;
                    if (elemento == NULL)
                        elemento = temporal;
                    else {
                        aux = elemento;
                        while (aux->next != NULL)
                            aux = aux->next;
                        aux->next = temporal;
                    }
                    pthread_create(hilo, NULL, lectura_archivos, (void*)siguiente);
                } else {
                    printf("es un archivo y fue copiado");
                    ruta_siguiente = malloc(sizeof(contenido->destino) + sizeof(contenido->ruta) + sizeof(archivo->d_name));
                    ruta_anterior = malloc(sizeof(origen) + sizeof(contenido->ruta) + sizeof(archivo->d_name));
                    copiar_archivo(ruta_siguiente, ruta_anterior, contenido, archivo->d_name);
                    free(ruta_siguiente);
                    free(ruta_anterior);
                }
            }
            free(archivo_dir);
        }
    }
    while (elemento != NULL) {
        pthread_join(*(elemento->hilo), NULL);
        elemento = elemento->next;
    }
    free(hilo);
    return NULL;
}

int copiar_archivo(char *ruta_siguiente, char *ruta_anterior, struct contenedor *contenido, char *archivo) {
    char buffer[1];
    strcpy(ruta_siguiente, contenido->destino);
    strcpy(ruta_anterior, contenido->origen);
    strcat(ruta_siguiente, contenido->ruta);
    strcat(ruta_anterior, contenido->ruta);
    strcat(ruta_siguiente, archivo);
    strcat(ruta_anterior, archivo);
    int archivo_origen = open(ruta_anterior, O_RDONLY);
    int archivo_copia = open(ruta_siguiente, O_WRONLY | O_CREAT, 0640);
    while (0 < read(archivo_origen, buffer, 1))
        write(archivo_copia, buffer, 1);
    close(archivo_origen);
    close(archivo_copia);
    return 0;
}

