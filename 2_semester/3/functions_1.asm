%include "io.inc"

section .data
x dw 5
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    mov ebp, esp
    xor eax, eax
    xor ebx, ebx
    push word [x]
    pop bx
    push word 15
    pop bx
    mov ax, 25
    push word ax
    pop bx
    ret