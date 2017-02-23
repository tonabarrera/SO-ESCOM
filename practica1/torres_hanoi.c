#include <stdio.h>
#include <math.h>
#include "pila.h"

int llenar_pila(struct Pila *torre, int N){
    for (; N > 0; N--)
        push(&torre, N);
    return 1;
}

int hanoi(int N, struct Pila *origen, struct Pila *aux, struct Pila *destino, int conteo){
    conteo++;
    int dato = 0;
    if (N==1) {
        dato = pop(&origen);
        push(&destino, dato);
        printf("Se movio el %d de la base %c a la base %c\n", dato, origen->nombre, destino->nombre);
    } else {
        conteo=hanoi(N-1, origen, destino, aux, conteo);
        dato = pop(&origen);
        push(&destino, dato);
        printf("Se movio el %d de la base %c a la base %c\n", dato, origen->nombre, destino->nombre);
        conteo=hanoi(N-1, aux, origen, destino, conteo);
    }
    return conteo;
}

int main(int argc, char *argv[]) {
    struct Pila *torre_A = NULL;
    struct Pila *torre_B = NULL;
    struct Pila *torre_C = NULL;
    int numero_discos = 0;
    int conteo = 0;
    printf("Ingresa el numero de discos (0<N<10): ");
    scanf("%d", &numero_discos);
    if (numero_discos == 0 || numero_discos>10) {
        printf("Dije 0<N<10");
        return 0;
    }
    iniciar_pila(&torre_A, 'A');
    iniciar_pila(&torre_B, 'B');
    iniciar_pila(&torre_C, 'C');
    llenar_pila(torre_A, numero_discos);
    conteo = hanoi(numero_discos, torre_A, torre_B, torre_C, conteo);
    printf("Numero de movimientos requeridos = %.0lf", (pow(2, numero_discos)-1));
    return 0;
}
