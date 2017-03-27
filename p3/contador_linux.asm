segment .data
    cadenaImprimir db '0',10  ;El 10=0xA es para que haga un salto de linea
    longitudCadena dd 2 ;Es de tamaño dos ya que cuenta el salto de linea
    contador dd 0

segment .text
    global _start

_start:
    xor eax,eax
    mov eax,0d
    ;Un poderoso do while
    ciclo:
        mov edx, 2d
	mov ecx, cadenaImprimir
	mov ebx, 1
	mov eax, 4
	int 0x80

        inc byte [cadenaImprimir] ;Agrega 1 byte al primer byte de nuestro numero
        inc dword [contador] ;Agrega 1 a la direccion de memoria
        mov eax, [contador] ;Lo cargamos
        cmp eax,10 ;if eax<10 entonces jb regresa al inicio de ciclo
        jb ciclo

    mov eax, 1
    int 0x80
