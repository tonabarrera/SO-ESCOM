#include <stdio.h>
#include <stdlib.h>
void evaluar_numero(int numero);
void imprimir_rombos(int numero);

int main() {
	printf("Ingresa el ancho que deseas para ambos rombos:  \n\n");
	int tam=0,repet=0;
	scanf("%d",&tam);
	evaluar_numero(tam);
	printf("\n\n Desea repetir el proceso?   si <1>     no <otra tecla>\n\n");
	scanf("%d",&repet);
	if(repet==1)
		main();
	else
		return 0;
}
void evaluar_numero(int numero) {
	int mitad=numero/2;
	int num_aux=0,num_aux1=mitad%2;
	num_aux=numero%2;
	if(numero<79){
		if(num_aux==0){
			if(num_aux1==0)
				printf("\n\nLo sentimos, no podemos trabajar con este numero :(\n\n");
			else
				imprimir_rombos(mitad);	
		}
		else
			printf("\n\nLo sentimos, no podemos trabajar con numeros impares :( \n\n");		
	}
	else
		printf("\n\nLo sentimos, tu numero es demasiado grande como para que el proceso se muestre en consola :(\n\n");
}
void imprimir_rombos(int numero){
//genera el contorno
	char mat[numero][numero]; 
	char mat2[numero][numero];
	FILE *archivo;
	archivo = fopen("./rombos.txt", "w");
	int i=0, j=0, m=0, n=0, k=0, p=numero/2,r=0,t=0, algo=0;	
	for(i=0;i<numero;i++){
		for(j=0;j<numero;j++){
			if(i<=numero/2){
				if((numero/2)-i==j)
					mat[i][j]='*';
				else
					mat[i][j]=' ';	
				mat[i][(numero/2)+i]='*';
			}
			else{
				if(k==j)
					mat[i][j]='*';
				else
					mat[i][j]=' ';	
				mat[i][(numero/2)+p]='*';
			}	
		}
		if(i>=numero/2){
			k++;
			p--;
		}
	}
// Genera la figura rellenada
	for(r=0;r<numero;r++){
		for(t=0;t<numero;t++) //llena de espacios la matriz
			mat2[r][t]=' ';
	}
	for(m=0;m<numero;m++){
		for(n=0;n<numero;n++){		
			if(m+n>=numero/2 && m+n<=numero/2+numero-1 )//genera romboide
				mat2[m][n]='*';				
		}
	}
	for(m=0;m<numero;m++){
		int tope=numero/2+1+m;
		for(n=0;n<numero;n++){
			if(m<numero/2){
				for(tope;tope<numero;tope++) //recorta esquinas 
					mat2[m][tope]=' ';
			}
			else if(m>numero/2){
				for(algo=0;algo<m-numero/2;algo++)
					mat2[m][algo]=' ';
			}
		}
	}
//imprime ambas matrices
	for(m=0;m<numero;m++){
		for(n=0;n<numero;n++){
			printf("%c",mat[m][n]);
			fputc(mat[m][n], archivo);
		}
		for(r=0;r<numero;r++){
			printf("%c",mat2[m][r]);
			fputc(mat2[m][r], archivo);
		}
		printf("\n");
		fputs("\n", archivo);
	}
	fclose(archivo);	
}

