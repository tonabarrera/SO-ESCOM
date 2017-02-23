#ifndef __PILA_H_
#define __PILA_H_

#include <stdio.h>
#include <stdlib.h>
//Creo que esta esctructura puede servir para el de los parentesis y el de la expresion
struct Nodo {
  int dato;
  struct Nodo *siguiente;
};

struct Pila {
  struct Nodo *top;
  char nombre;
};
void iniciar_pila(struct Pila **, char);
int push(struct Pila **, int);
int pop(struct Pila **);
int vacio(struct Pila *);
#endif
