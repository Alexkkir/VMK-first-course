%include "io.inc"

section .bss
    a resd 1
    d resd 1
    
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, [a]
    mov eax, [a]
    cmp eax, 2
    je bad_input
    mov eax, 2
    mov [d], eax

cyc:
    mov edx, 0
    mov eax, [a]
    mov ecx, [d]
    cdq
    div ecx
    
    cmp edx, 0
    je ans
    inc ecx
    mov [d], ecx
    jmp cyc
    
bad_input:
    PRINT_DEC 4, 1
    mov eax, 0
    ret

ans:
    mov edx, 0
    mov eax, [a]
    mov ecx, [d]
    cdq
    div ecx
    PRINT_DEC 4, eax
    mov eax, 0
    ret
    

    
    
    
    
    