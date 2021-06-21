%include "io.inc"

section .bss
    a resd 1
    b resd 1
section .text
global CMAIN
CMAIN:
    ;write your code here
    GET_DEC 4, [a]
    GET_DEC 4, [b]

cyc:
    mov eax, [a]
    mov edx, 0
    
    mov ecx, [b]
    cdq
    
    div ecx
    
    mov eax, [b]
    mov [a], eax
    mov [b], edx
    
    cmp edx, 0
    jne cyc
    PRINT_DEC 4, [a]
    mov eax, 0
    ret