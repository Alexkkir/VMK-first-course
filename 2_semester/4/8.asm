%include "io.inc"

section .data
    ans dd 0
    sum dd 0
    k dd 0
    x dd 0
    y dd 0
    t dd 0
section .text
global CMAIN
CMAIN:
    ;write your code here
    GET_UDEC 4, [y]
    mov eax, [y]
    mov [ans],eax
    GET_UDEC 4, [k]
    .do:
        mov eax, [y]
        mov [x], eax
        
        mov [sum], dword 0
        mov eax, [x]
        mov [t], eax
        .while2:
            cmp [t], dword 0
            jle .stop
            mov eax, [t]
            mov edx, dword 0
            mov ebx, [t]
            cdq
            div dword [k]
            add [sum], edx
            mov [t], eax
            jmp .while2
        .stop:
        mov eax, [sum]
        mov [y], eax
        mov eax, [y]
        add [ans], eax
     .while:
        mov eax, [y]
        cmp [x], eax
        jne .do
    PRINT_UDEC 4, [ans]
    
    xor eax, eax
    ret