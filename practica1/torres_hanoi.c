#include <stdio.h>
#include <math.h>
#include "pila.h"
int llenar_pila(struct Pila *torre, int N){
    for (; N > 0; N--)
        push(&torre, N+'0');
    return 1;
}
int hanoi(int N, struct Pila *origen, struct Pila *aux, struct Pila *destino, int conteo){
    conteo++;
    char dato = 0;
    if (N==1) {
        dato = pop(&origen);
        push(&destino, dato);
        printf("Se movio el %c de la base %c a la base %c\n", dato, origen->nombre, destino->nombre);
    } else {
        conteo=hanoi(N-1, origen, destino, aux, conteo);
        dato = pop(&origen);
        push(&destino, dato);
        printf("Se movio el %c de la base %c a la base %c\n", dato, origen->nombre, destino->nombre);
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
    printf("Ingresa el numero de discos: ");
    scanf("%d", &numero_discos);
    iniciar_pila(&torre_A, 'A');
    iniciar_pila(&torre_B, 'B');
    iniciar_pila(&torre_C, 'C');
    llenar_pila(torre_A, numero_discos);
    conteo = hanoi(numero_discos, torre_A, torre_B, torre_C, conteo);
    printf("Numero de movimientos requeridos = %d\n", conteo);
    return 0;
}
