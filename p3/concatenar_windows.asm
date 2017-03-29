segment .data
    handle_salida dd 0
    msj_bytes dd 0
    msj_bytes2 dd 0
    msj1 db "Ingrese la cadena 1", 10
    msj2 db "Ingrese la cadena 2", 10
    msj3 db "Ingrese la cadena 3", 10
    final db "Cadena final: "
    terminado dd 0

    handle_entrada dd 0
    cadena_bytes dd 0
segment .bss
    cadena1 resb 150
    cadena2 resb 150
    cadena3 resb 150
    cadena_final resb 450
segment .text
    global _main
    extern _GetStdHandle@4
    extern _WriteConsoleA@20
    extern _ReadConsoleA@20
    extern _ExitProcess@4
_main: push -11
    call _GetStdHandle@4
    mov [handle_salida], eax

    xor eax, eax
    push dword -10
    call _GetStdHandle@4
    mov [handle_entrada],eax
    ; Cadena 1
    push 0
    push dword msj_bytes
    push 20
    push dword msj1
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena1
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ; Cadena 2
    push 0
    push dword msj_bytes
    push 20
    push dword msj2
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena2
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ; Cadena 3
    push 0
    push dword msj_bytes
    push 20
    push dword msj3
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena3
    push dword [handle_entrada]
    call dword _ReadConsoleA@20

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
    push 0
    push dword msj_bytes2
    push 14
    push dword final
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword msj_bytes
    push 450
    push dword cadena_final
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    call _ExitProcess@4
