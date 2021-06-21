%include "io.inc"

section .data    
    n1 dd 3, n2
    n2 dd 4, 0
    

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    push ebp
    mov ebp, esp
    
    push n1
    call f
    
    PRINT_DEC 4, eax
    
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
    ret
    
f:
    cmp dword[esp+4], 0
    mov eax, 1
    je .end
    
    sub esp, 4
    mov edx, dword[esp+8]
    movsx eax, word[edx]
    push eax
    push dword[edx+4]
    call f
    mov ecx, dword[esp+4]
    imul eax, ecx
    add esp, 12
    ret
    
    .end:
    ret