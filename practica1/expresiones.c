#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "cola.h"
int calcular_total(struct Elemento *caracter);
int reeordenar(char *cadena, struct Cola *salida, struct Pila *operadores);

int main(int argc, char* argv[])
{
    char cadena[100];
    struct Pila *operadores = NULL;
    struct Cola *salida = NULL;
    iniciar_pila(&operadores, '0');
    iniciar_cola(&salida);
    printf("%s\n", "Inserta una expresion matematica correctamente escrita");
    fflush(stdin);
    fgets (cadena, 100, stdin);
    reeordenar(cadena, salida, operadores);
    return 0;
}
int reeordenar(char *cadena, struct Cola *salida, struct Pila *operadores){
    int i = 0;
	while (cadena[i] != '\0'){
    	if(cadena[i] == '(')
    		push(&operadores, cadena[i]);
    	else if (cadena[i] == ')'){
    		while (!esta_vacio(operadores)){
    			char elemento = pop(&operadores);
    			if ( elemento == '('){ break; }
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
			} else { push(&operadores, operador); }
			
			push(&operadores, cadena[i]);
    	} else if((int)cadena[i] != 10){ meter(&salida, cadena[i]); }
    	i++;
    }
    while (!esta_vacio(operadores)){
		char elemento = pop(&operadores);
		meter(&salida, elemento);
	}
	calcular_total(salida->inicio);
	return 0;
}
int calcular_total(struct Elemento *caracter){
	double a = 0;
    double b = 0;
    struct Pila *final = NULL;
    iniciar_pila(&final, '0');

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
