%include "io.inc"

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    sub esp, 12
    GET_DEC 4, [esp]
    GET_DEC 4, [esp+4]
    GET_DEC 4, [esp+8]
    call my_add
    PRINT_DEC 4, eax
    mov esp, ebp
    pop ebp
    ret
    
my_add:
    enter 12, 1
    mov eax, dword [ebp - 4]
    add eax, dword [ebp - 8]
    add eax, dword [ebp - 12]
    leave
    ret