segment .data
    msj db "Ingresa una cadena para obtener su longitud", 10
    msj2 db "La longitud es: "
    salto db 10
    longitud dd 0
    longitud_final dd 0
segment .bss
    cadena resb 150
segment .text
global _start

_start:
    mov edx, 44d
    mov ecx, msj
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov edx, 150d
    mov ecx, cadena
    mov ebx, 0
    mov eax, 3
    int 0x80

    xor esi, esi
    ciclo:
        ; Valores raros que agrega la entrada en teclado podria solo dejar una y restar dos pero nah o longitud-=2
        mov al, [cadena+esi]
        cmp al, 0
        je continuar
        cmp al, 10
        je continuar
        cmp al, 13
        je continuar

        inc dword [longitud]
        inc esi
        jmp ciclo

    continuar:
    xor eax,eax
    mov eax, [longitud]
    cosa:
        xor edx,edx
        mov edx,0
        mov ecx, 10
        div ecx
        add edx,48
        push edx
        cmp eax,0
        jne cosa

    mov edx, 16d
    mov ecx, msj2
    mov ebx, 1
    mov eax, 4
    int 0x80

    imprimir:
        pop edx
        cmp edx, 48
        jl terminar
        cmp edx, 57
        jg terminar
        mov [longitud_final], edx

        mov edx, 1d
	mov ecx, longitud_final
	mov ebx, 1
	mov eax, 4
	int 0x80

        jmp imprimir

    terminar:
    mov edx, 1d
	mov ecx, salto
	mov ebx, 1
	mov eax, 4
	int 0x80
    mov eax, 1
    int 0x80
