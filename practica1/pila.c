#include "pila.h"

void iniciar_pila(struct Pila **pila, char nombre) {
    *pila = (struct Pila *) malloc(sizeof(struct Pila));
    if(*pila == NULL)
        return;
    (*pila)->top = NULL;
    (*pila)->nombre = nombre;
    return;
}

int vacio(struct Pila *pila){
    if(pila->top == NULL)
        return 1;
    else
        return 0;
}

int push(struct Pila **pila, int val) {
    struct Nodo *temp = NULL;
    temp = (struct Nodo *) malloc(sizeof(struct Nodo));
    if(temp == NULL)
        return 0;

    temp->dato = val;
    temp->siguiente = (*pila)->top;
    (*pila)->top = temp;

    return 1;
}

int pop(struct Pila **pila){
    int pop = (*pila)->top->dato;
    struct Nodo *temp = NULL;
    temp = (struct Nodo *) malloc(sizeof(struct Nodo));
    if(temp == NULL)
        return 0;
    temp = (*pila)->top;
    (*pila)->top = temp->siguiente;
    free(temp);
    temp = NULL;
    return pop;
}
