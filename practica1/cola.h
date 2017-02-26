#ifndef __COLA_H_
#define __COLA_H_

#include <stdio.h>
#include <stdlib.h>

struct Elemento {
	char dato;
	struct Elemento *siguiente;
};

struct Cola {
	struct Elemento *inicio;
	struct Elemento *final;
};
void iniciar_cola(struct Cola **);
int meter(struct Cola **, char);
char sacar(struct Cola **);
#endif