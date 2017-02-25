#ifndef __PILA_H_
#define __PILA_H_

#include <stdio.h>
#include <stdlib.h>

struct Nodo {
  char dato;
  struct Nodo *siguiente;
};

struct Pila {
  struct Nodo *top;
  char nombre;
};
void iniciar_pila(struct Pila **, char);
int push(struct Pila **, char);
char pop(struct Pila **);
#endif
