//BALANCE DE PARENTESIS CON PILAS
#include <stdio.h>
#include <stdlib.h>
#include <Pila.h>

//--------------Verifica si la expresión ingresada, está o no balanceada
int esBalanceada(char expresion[], char abre, char cierra){
	int x=0, balance=1;
	Pila p = empty();
	while (expresion[x] != '\0' && balance == 1){// Recorre la cadena
		if (expresion[x]==abre){// Si es parentesis que abre, lo ingresa en la pila
		p=push(expresion[x], p);
	} else{
		if (expresion[x]==cierra){// Si el elemento coincide con el caracter que cierra
			if (isempty(p) != 1){//Si la pila no está vacía
				p=pop(p);
			} else {//Si la pila está vacía, no puede sacar ningún elemento y por tanto, no está balanceada
				balance = 0;
			}
		}
	}
	x++;
	}
//Si balance = 1 pero la pila no está vacía, entonces quedaron caracteres que abren sin tener su caracter que cierra
 	if (balance == 1 && isempty(p) != 1){  balance = 0; }
//Hacemos que la pila esté vacía para otra expresión
//p=empty();
 	return balance; 
}

void balanceGeneral(char expresion[]){
	if((esBalanceada(expresion, '{','}') && esBalanceada(expresion, '[', ']') && esBalanceada(expresion, '(', ')'))==1){
 		printf("Expresion balanceada");
	}
 	else{ printf("Expresion NO balanceada");}
}

int main(){
	int repetir,c;
	do{
		char cadena[100];
		printf("Ingrese una expresion:\n");
		gets(cadena);
	    balanceGeneral(cadena);
		printf("\n\nPresione 1 para ingresar otra expresion, o cualquier otro numero para finalizar\n");
		scanf("%d",&repetir);
		while ((c = getchar()) != '\n' && c != EOF);
	} while(repetir==1);
 	return 0;
}
 
