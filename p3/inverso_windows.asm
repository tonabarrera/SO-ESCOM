segment .data
    handle_salida dd 0
    msj_bytes dd 0
    msj_bytes2 dd 0
    msj1 db "Ingrese la cadena 1", 10
    msj2 db "Ingrese la cadena 2", 10
    msj3 db "Ingrese la cadena 3", 10
    msj4 db "Ingrese la cadena 4", 10
    msj5 db "Ingrese la cadena 5", 10
    msj6 db "Ingrese la cadena 6", 10
    msj7 db "Ingrese la cadena 7", 10
    msj8 db "Ingrese la cadena 8", 10
    msj9 db "Ingrese la cadena 9", 10
    msj10 db "Ingrese la cadena 10", 10
    longitudmsj db "La longitud final es: "
    salto_linea db 10
    final db "Cadena final: "
    final2 db "Cadena final al revez: "
    terminado dd 0
    longitud dd 0
    aux db ""
    longitud_cadena dd 0
    longitud_final dd 0
    caracter db ""

    handle_entrada dd 0
    cadena_bytes dd 0
segment .bss
    cadena1 resb 150
    cadena2 resb 150
    cadena3 resb 150
    cadena4 resb 150
    cadena5 resb 150
    cadena6 resb 150
    cadena7 resb 150
    cadena8 resb 150
    cadena9 resb 150
    cadena10 resb 150
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

    ; Cadena 4
    push 0
    push dword msj_bytes
    push 20
    push dword msj4
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena4
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ; Cadena 5
    push 0
    push dword msj_bytes
    push 20
    push dword msj5
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena5
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ; Cadena 6
    push 0
    push dword msj_bytes
    push 20
    push dword msj6
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena6
    push dword [handle_entrada]
    call dword _ReadConsoleA@20

    ; Cadena 7
    push 0
    push dword msj_bytes
    push 20
    push dword msj7
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena7
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ; Cadena 8
    push 0
    push dword msj_bytes
    push 20
    push dword msj8
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena8
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ; Cadena 9
    push 0
    push dword msj_bytes
    push 20
    push dword msj9
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena9
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ; Cadena 10
    push 0
    push dword msj_bytes
    push 21
    push dword msj10
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword cadena_bytes
    push 150
    push dword cadena10
    push dword [handle_entrada]
    call dword _ReadConsoleA@20
    ;Ciclos para copiar cada cadena en la cadena final
    xor edi, edi
    xor al, al
    xor esi, esi
    ciclo1:
        mov al, [cadena1+edi]
        cmp al, 0
        je ciclo2
        cmp al, 10
        je ciclo2
        cmp al, 13
        je ciclo2
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo1
    ciclo2:
    xor edi, edi
    xor al, al
    ciclo2a:
        mov al, [cadena2+edi]
        cmp al, 0
        je ciclo3
        cmp al, 10
        je ciclo3
        cmp al, 13
        je ciclo3
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo2a
    ciclo3:
    xor edi, edi
    xor al, al
    ciclo3a:
        mov al, [cadena3+edi]
        cmp al, 0
        je ciclo4
        cmp al, 10
        je ciclo4
        cmp al, 13
        je ciclo4
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo3a
    ciclo4:
    xor edi, edi
    xor al, al
    ciclo4a:
        mov al, [cadena4+edi]
        cmp al, 0
        je ciclo5
        cmp al, 10
        je ciclo5
        cmp al, 13
        je ciclo5
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo4a
    ciclo5:
    xor edi, edi
    xor al, al
    ciclo5a:
        mov al, [cadena5+edi]
        cmp al, 0
        je ciclo6
        cmp al, 10
        je ciclo6
        cmp al, 13
        je ciclo6
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo5a

    ciclo6:
    xor edi, edi
    xor al, al
    ciclo6a:
        mov al, [cadena6+edi]
        cmp al, 0
        je ciclo7
        cmp al, 10
        je ciclo7
        cmp al, 13
        je ciclo7
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo6a

    ciclo7:
    xor edi, edi
    xor al, al
    ciclo7a:
        mov al, [cadena7+edi]
        cmp al, 0
        je ciclo8
        cmp al, 10
        je ciclo8
        cmp al, 13
        je ciclo8
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo7a

    ciclo8:
    xor edi, edi
    xor al, al
    ciclo8a:
        mov al, [cadena8+edi]
        cmp al, 0
        je ciclo9
        cmp al, 10
        je ciclo9
        cmp al, 13
        je ciclo9
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo8a

    ciclo9:
    xor edi, edi
    xor al, al
    ciclo9a:
        mov al, [cadena9+edi]
        cmp al, 0
        je ciclo10
        cmp al, 10
        je ciclo10
        cmp al, 13
        je ciclo10
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo9a

    ciclo10:
    xor edi, edi
    xor al, al
    ciclo10a:
        mov al, [cadena10+edi]
        cmp al, 0
        je final_concatenar
        cmp al, 10
        je final_concatenar
        cmp al, 13
        je final_concatenar
        mov [cadena_final+esi], al
        inc edi
        inc esi
        jmp ciclo10a
    ; Se procede a imprimir la longitud
    final_concatenar:
    ; Vamo a ver
    mov [longitud], esi
    xor esi, esi
    xor edi, edi
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
    push dword 22
    push dword longitudmsj
    push dword [handle_salida]
    call _WriteConsoleA@20

    imprimir:
        pop edx
        cmp edx, 48
        jl siguiente
        cmp edx, 57
        jg siguiente
        mov [longitud_final], edx

        push 0
        push dword msj_bytes
        push dword 1
        push dword longitud_final
        push dword [handle_salida]
        call _WriteConsoleA@20

        jmp imprimir

    siguiente:
    push 0
    push dword msj_bytes
    push dword 1
    push dword salto_linea
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword msj_bytes2
    push 14
    push dword final
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword msj_bytes
    push dword [longitud]
    push dword cadena_final
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword msj_bytes
    push dword 1
    push dword salto_linea
    push dword [handle_salida]
    call _WriteConsoleA@20

    push 0
    push dword msj_bytes2
    push 23
    push dword final2
    push dword [handle_salida]
    call _WriteConsoleA@20
    ;Aqui se voltea la cadena
    xor edi, edi
    xor esi, esi
    xor al, al
    xor eax, eax
    mov edi, cadena_final
    add edi, [longitud]
    sub edi, 1
    super_loop:
        lea eax, [esi+edi]
        cmp eax, 0
        je terminar
        cmp eax, 10
        je terminar
        cmp eax, 13
        je terminar
        cmp eax, 32
        je terminar
        push 0
        push dword msj_bytes
        push 1
        push eax
        push dword [handle_salida]
        call _WriteConsoleA@20
        terminar:
        dec edi
        mov al, [esi+edi]
        or al, al
        jne super_loop

    push 0
    call _ExitProcess@4
