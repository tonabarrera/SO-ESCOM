//ESTRUCTURA PILA
#include <stdio.h>
#include <stdlib.h>
 
typedef struct nodoP{
    char dato;
    struct nodoP *sig;
}* Pila;

//-------------------VACIA
Pila empty(){return NULL; }

//-------------------CONSTRUYE
Pila push(char e, Pila p){
	Pila temp = (Pila) malloc (sizeof(struct nodoP));
	temp->dato=e;//mete el valor de dato del nodo al que apunta temp
	temp->sig=p;
    return temp;
}

//------------------ES VACIA
int isempty(Pila p){return p==NULL;}

//-------------------CABEZA
char top(Pila p){return p->dato;}


//-------------------RESTO
Pila pop(Pila p){return p->sig;}

//-------------------IMPRIME PILA (nodo por nodo)
void nodosPila(Pila p){
    if (isempty(p) == 1)
        printf("La pila está vacia\n");
    else{
        while (p->sig != NULL){
            printf("%c\n",p->dato);
            p= p->sig;
        }
        printf("\n");
    }
}
