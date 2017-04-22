#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hilo(void *arg);

int main(int argc, char const* argv[])
{
    pthread_t id_hilo;
    char *mensaje = "Hola a todos desde el hilo";
    int *devolucion_hilo = malloc(sizeof(int));
    pthread_create(&id_hilo, NULL, hilo, (void*)mensaje);
    pthread_join(id_hilo, (void*)devolucion_hilo);
    printf("Valor=%i\n", *devolucion_hilo);
    return 0;
}

void *hilo(void *arg) {
    char *men;
    int *resultado_hilo = malloc(sizeof(int));
    men = (char*)arg;
    printf("%s\n", men);
    *resultado_hilo = 100;
    pthread_exit((void*)48);
    printf("No %i\n", *resultado_hilo);
    return (void*)resultado_hilo;
}
