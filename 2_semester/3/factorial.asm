%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;write your code here
    mov ebp, esp
    push ebp
    mov ebp, esp
    sub esp, 4
    GET_DEC 4, [esp]
    call factorial
    PRINT_DEC 4, eax
    mov esp, ebp
    pop ebp
    ret
    
factorial:
    enter 4, 1
    mov ecx, dword [ebp - 8]
    mov eax, 1
    cmp ecx, 0
    je .zero
    .cycl:
        imul eax, ecx
        dec ecx
        cmp ecx, 0
        jne .cycl
    .zero:
    leave
    ret