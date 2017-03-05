#ifndef __PILA_H_
#define __PILA_H_

#include <stdio.h>
#include <stdlib.h>

struct Nodo {
	char dato;
	double dato2;
	struct Nodo *siguiente;
};

struct Pila {
	struct Nodo *top;
	char nombre;
};
void iniciar_pila(struct Pila **, char);
int push(struct Pila **, char);
char pop(struct Pila **);
int push_double(struct Pila **, double);
double pop_double(struct Pila **);
int esta_vacio(struct Pila *);
#endif
