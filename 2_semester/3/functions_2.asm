%include "io.inc"

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    GET_DEC 4, [esp]
    GET_DEC 4, [esp + 4]
    call my_add
    PRINT_DEC 4, eax
    leave
    ret
    
    
    
my_add:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp - 4] ; or ebp + 8 on linux
    ;add eax, dword[ebp - 8] ; or ebp + 12
    mov esp, ebp
    pop ebp
    ret