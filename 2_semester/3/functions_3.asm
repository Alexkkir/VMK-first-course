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
    leave
    ret
    
my_add:
    push ebp
    mov ebp, esp
    mov eax, dword [ebp]
    ;add eax, dword [ebp - 12]
    ;add eax, dword [ebp - 16]
    mov esp, ebp
    pop ebp
    ret