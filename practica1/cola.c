#include "cola.h"
void iniciar_cola(struct Cola **cola) {
    *cola = (struct Cola *) malloc(sizeof(struct Cola));
    if(*cola == NULL)
        return;
    (*cola)->inicio = NULL;
    (*cola)->final = NULL;
    return;
}
int meter(struct Cola **cola, char val) {
    struct Elemento *temp = NULL;
    temp = (struct Elemento *) malloc(sizeof(struct Elemento));
    if(temp == NULL)
        return 0;
    temp->dato = val;
    temp->siguiente = NULL;
    if ((*cola)->final == NULL){
        (*cola)->final = temp;
        (*cola)->inicio = temp;
    } else {
        (*cola)->final->siguiente = temp;
        (*cola)->final = temp;
    }
    return 1;
}
char sacar(struct Cola **cola){ 
    char dato = (*cola)->inicio->dato;
    struct Elemento *temp = NULL;
    temp = (struct Elemento *) malloc(sizeof(struct Elemento));
    if(temp == NULL)
        return '0';
    temp = (*cola)->inicio;
    (*cola)->inicio = temp->siguiente;
    free(temp);
    temp = NULL;
    return dato;
}