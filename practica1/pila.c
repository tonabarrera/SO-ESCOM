#include "pila.h"

void iniciar_pila(struct Pila **pila, char nombre) {
    *pila = (struct Pila *) malloc(sizeof(struct Pila));
    if(*pila == NULL)
        return;
    
    (*pila)->top = NULL;
    (*pila)->nombre = nombre;
    return;
}

int push(struct Pila **pila, char val) {
    struct Nodo *temp = NULL;
    temp = (struct Nodo *) malloc(sizeof(struct Nodo));
    if(temp == NULL)
        return 0;

    temp->dato = val;
    temp->siguiente = (*pila)->top;
    (*pila)->top = temp;
    return 1;
}

int push_double(struct Pila **pila, double val) {
    struct Nodo *temp = NULL;
    temp = (struct Nodo *) malloc(sizeof(struct Nodo));
    if(temp == NULL)
        return 0;

    temp->dato2 = val;
    temp->siguiente = (*pila)->top;
    (*pila)->top = temp;
    return 1;
}

char pop(struct Pila **pila){
    if (esta_vacio(*pila))
        return '0';
    
    char pop_dato = (*pila)->top->dato;
    struct Nodo *temp = NULL;
    temp = (struct Nodo *) malloc(sizeof(struct Nodo));
    if(temp == NULL)
        return '0';
    temp = (*pila)->top;
    (*pila)->top = temp->siguiente;
    free(temp);
    temp = NULL;
    return pop_dato;
}

double pop_double(struct Pila **pila){
    if (esta_vacio(*pila))
        return '0';
    
    double pop_dato = (*pila)->top->dato2;
    struct Nodo *temp = NULL;
    temp = (struct Nodo *) malloc(sizeof(struct Nodo));
    if(temp == NULL)
        return '0';
    temp = (*pila)->top;
    (*pila)->top = temp->siguiente;
    free(temp);
    temp = NULL;
    return pop_dato;
}

int esta_vacio(struct Pila *pila) {
    if (pila->top==NULL)
    {
        return 1;
    }
    return 0;
}