#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *suma(void *arg);
void *resta(void *arg);
void *multiplicacion(void *arg);
void *transpuesta(void *arg);
void *inversa(void *argv);

int main(int argc, char const* argv[]) {
    int numero_hilos = 5;
    int prueba[2] = {90, 777};
    pthread_t *hilos = malloc(numero_hilos * sizeof(pthread_t));
    printf("Ejecutando los hilos...\n");
    pthread_create(&hilos[0], NULL, suma, prueba);
    pthread_create(&hilos[1], NULL, resta, prueba);
    pthread_create(&hilos[2], NULL, multiplicacion, prueba);
    pthread_create(&hilos[3], NULL, transpuesta, prueba);
    pthread_create(&hilos[4], NULL, inversa, prueba);
    int i;
    for (i=0; i<numero_hilos; i++)
        pthread_join(hilos[i], NULL);
    printf("El valor aqui es de %i\n", prueba[0]);
    printf("Imprimiendo el contenido de los archivos...\n");
    printf("Suma\n");
    printf("Resta\n");
    printf("Multiplicacion\n");
    printf("Transpuesta\n");
    printf("Inversa\n");
    free(hilos);
    return 0;
}

void *suma(void *arg) {
    printf("Realizando suma de matrices...\n");
    return NULL;
}
void *resta(void *arg) {
    printf("Realizando resta de matrices...\n");
    return NULL;
}
void *multiplicacion(void *arg) {
    printf("Realizando multiplicacion de matrices...\n");
    return NULL;
}
void *transpuesta(void *arg) {
    printf("Realizando transpuesta de matrices...\n");
    return NULL;
}
void *inversa(void *arg) {
    printf("Realizando inversa de matrices...\n");
    return NULL;
}
