%include "io.inc"
    
section .data
    x dd 0
    y dd 0
    z dd 0
    
    a1 dd 0
    a0 dd 0
    
    p1 dd 0
    p0 dd 0
    q1 dd 0
    q0 dd 0
    
    w2 dd 0
    w1 dd 0
    w0 dd 0
    
    len dd 0
    
section .bss
    ans resd 35

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    
    GET_UDEC 4, [x]
    GET_UDEC 4, [y]
    GET_UDEC 4, [z]
    
    ; multiplying x by y using extanded MUL (edx:eax)
    mov eax, [x]
    mul dword [y]
    mov [a1], edx
    mov [a0], eax
    
    ;multiplying a_0 (lower part) on z. Answer in q
    mov eax, [a0]
    mul dword [z]
    mov [q1], edx
    mov [q0], eax
    
    ;the same but for older part. Answer in p
    mov eax, [a1]
    mul dword [z]
    mov [p1], edx
    mov [p0], eax
    
    ;finally, we need to construct the answer
    ;wo (younger)
    mov eax, [q0]
    mov [w0], eax
    
    ;w1 (middle)
    mov eax, [q1]
    mov ebx, [p0]
    mov [w1], ebx
    add [w1], eax
    
    ;w2 (older). Remember about carry
    mov eax, [p1]
    mov [w2], eax
    adc [w2], dword 0
    
    
    ;The hardest step: dividing numbers
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
    cmp ecx, 0
    jne .len_is_not_0
    PRINT_CHAR '0'
    mov eax, 0
    ret
    
    .len_is_not_0:
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