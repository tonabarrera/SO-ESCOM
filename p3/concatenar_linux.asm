segment .data
    msj1 db "Ingrese la cadena 1", 10
    msj2 db "Ingrese la cadena 2", 10
    msj3 db "Ingrese la cadena 3", 10
    final db "Cadena final: "
    terminado dd 0
    salto db 10

segment .bss
    cadena1 resb 150
    cadena2 resb 150
    cadena3 resb 150
    cadena_final resb 450
segment .text
    global _start
_start:
    ; Cadena 1
    mov edx, 20d
    mov ecx, msj1
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov edx, 150d
    mov ecx, cadena1
    mov ebx, 0
    mov eax, 3
    int 0x80
    ; Cadena 2
    mov edx, 20d
    mov ecx, msj2
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov edx, 150d
    mov ecx, cadena2
    mov ebx, 0
    mov eax, 3
    int 0x80
    ; Cadena 3
    mov edx, 20d
    mov ecx, msj3
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov edx, 150d
    mov ecx, cadena3
    mov ebx, 0
    mov eax, 3
    int 0x80

    xor esi, esi
    xor edi, edi
    xor al, al
    ciclo:
        mov al, [cadena1+edi]
        cmp al, 0
        je prueba
        cmp al, 10
        je prueba
        cmp al, 13
        je prueba
        mov [cadena_final+esi], al
        inc esi
        prueba:
        mov al, [cadena2+edi]
        cmp al, 0
        je prueba1
        cmp al, 10
        je prueba1
        cmp al, 13
        je prueba1
        mov [cadena_final+esi], al
        inc esi
        prueba1:
        mov al, [cadena3+edi]
        cmp al, 0
        je prueba2
        cmp al, 10
        je prueba2
        cmp al, 13
        je prueba2
        mov [cadena_final+esi], al
        inc esi
        prueba2:
        inc edi

        mov al, [cadena2+edi]
        or al, [cadena1+edi]
        or al, [cadena3+edi]
        cmp al, 0
        je final
        jmp ciclo
    final:
    ; Vamo a ver
    mov edx, 14d
    mov ecx, final
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov edx, 450d
    mov ecx, cadena_final
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov edx, 1d
    mov ecx, salto
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov eax, 1
    int 0x80
