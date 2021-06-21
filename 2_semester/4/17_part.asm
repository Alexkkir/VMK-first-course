%include "io.inc"

section .data
    w2 dd 1
    w1 dd 0
    w0 dd 0
    len dd 0

section .bss
    ans resd 35
    
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    
    jmp .while1
    .do1:
        mov eax, [w2]
        mov edx, dword 0
        mov ecx, dword 10
        div ecx
        mov [w2], eax
        
        mov eax, [w1]
        mov ecx, dword 10
        div ecx
        mov [w1], eax
        
        mov eax, [w0]
        mov ecx, dword 10
        div ecx
        mov [w0], eax
        
        mov ebx, [len]
        mov dword [ans + 4 * ebx], edx
        inc ebx
        mov [len], ebx
        
    .while1:
        mov eax, [w2]
        or eax, [w1]
        or eax, [w0]
        cmp eax, 0
        jne .do1
    
    mov ecx, [len]
    dec ecx
    jmp .for2
    .do2:
        mov eax, dword [ans + 4 * ecx]
        call print_eax
        dec ecx
    .for2:
        cmp ecx, 0
        jge .do2
    
    xor eax, eax
    ret
print_eax:
    PRINT_DEC 4, eax
    ret