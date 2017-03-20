segment .data
    handle_salida dd 0
    msj_bytes dd 0
    msj db "Ingresa una cadena para obtener su longitud", 10
    msj2 db "La longitud es: "
    handle_entrada dd 0
    cadena_bytes dd 0
    longitud dd 0
    longitud_final dd 0
segment .bss
    cadena resb 150
segment .text
global _main
extern _GetStdHandle@4
extern _WriteConsoleA@20
extern _ReadConsoleA@20
extern _ExitProcess@4

_main: push -11
    call _GetStdHandle@4
    mov [handle_salida], eax

    push 0
    push dword msj_bytes
    push 44
    push dword msj
    push dword [handle_salida]
    call _WriteConsoleA@20

    xor eax, eax
    push dword -10
    call _GetStdHandle@4
    mov [handle_entrada],eax

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena
    push dword [handle_entrada]
    call dword _ReadConsoleA@20

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

    push 0
    push dword msj_bytes
    push dword 16
    push dword msj2
    push dword [handle_salida]
    call _WriteConsoleA@20

    imprimir:
        pop edx
        cmp edx, 48
        jl terminar
        cmp edx, 57
        jg terminar
        mov [longitud_final], edx

        push 0
        push dword msj_bytes
        push dword 1
        push dword longitud_final
        push dword [handle_salida]
        call _WriteConsoleA@20

        jmp imprimir

    terminar:
    push 0
    call _ExitProcess@4
