#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "cola.h"

int main(int argc, char* argv[])
{
    char cadena[100];
    struct Pila *operadores = NULL;
    struct Cola *salida = NULL;
    struct Pila *final = NULL;
    double a;
    double b;
    iniciar_pila(&operadores, '0');
    iniciar_pila(&final, '0');
    iniciar_cola(&salida);
    int i = 0;
    printf("%s\n", "Inserta una expresion matematica correctamente escrita");
    fflush(stdin);
    fgets (cadena, 100, stdin);
    while (cadena[i] != '\0'){
    	printf("El dato es: %d\n", cadena[i]);
    	if(cadena[i] == '(')
    		push(&operadores, cadena[i]);
    	else if (cadena[i] == ')'){
    		while (!esta_vacio(operadores)){
    			char elemento = pop(&operadores);
    			if ( elemento == '(')
    				break;
    			meter(&salida, elemento);
    		}
    	} else if(cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*' || cadena[i] == '/') {
    		char operador = pop(&operadores);
			while(operador == '+' || operador == '-' || operador == '*' || operador == '/'){
				if(cadena[i] == '-' || cadena[i] == '/'){
					if((cadena[i] == '/' && operador =='-')||(cadena[i] == '/' && operador =='+')){
						push(&operadores, operador);
						break;
					} else {
						meter(&salida, operador);
					}
				} else {
					if((cadena[i] == '+' && operador=='*') || (cadena[i] == '+' && operador=='/')){
						meter(&salida, operador);
					} else {
						push(&operadores, operador);
						break;
					}
				}
				operador = pop(&operadores);
			}
			if (operador == '+' || operador == '-' || operador == '*' || operador == '/' || operador == '0'){	
			} else {
				push(&operadores, operador);
			}
			push(&operadores, cadena[i]);

    	} else if((int)cadena[i] != 10){
			printf("%s %c\n", "Metio", cadena[i]);
			meter(&salida, cadena[i]);
    	}
    	i++;
    }
    while (!esta_vacio(operadores)){
		char elemento = pop(&operadores);
    	printf("%s %c\n", "Algo", elemento);
		meter(&salida, elemento);
	}
	struct Elemento *caracter = salida->inicio;
		while(caracter != NULL){
			if(caracter->dato == '+'){
				a = pop_double(&final);
				b = pop_double(&final);

				push_double(&final, b+a);
			} else if(caracter->dato == '-'){
				a = pop_double(&final);
				b = pop_double(&final);

				push_double(&final, b-a);
			} else if(caracter->dato == '/'){
				a =pop_double(&final);
				b = pop_double(&final);
				push_double(&final, b/a);

			} else if(caracter->dato == '*'){
				a = pop_double(&final);
				b = pop_double(&final);
				push_double(&final, b*a);
			} else {
				push_double(&final, (caracter->dato)-'0');
			}
			caracter = caracter->siguiente;
		}
		printf("El total: %lf\n", pop_double(&final));

    return 0;
}
