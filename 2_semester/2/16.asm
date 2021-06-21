%include "io.inc"

section .bss
    a11 resd 1
    a12 resd 1
    a21 resd 1
    a22 resd 1
    b1 resd 1
    b2 resd 1
    
section .text
global CMAIN
CMAIN:
    GET_UDEC 4, a11
    GET_UDEC 4, a12
    GET_UDEC 4, a21
    GET_UDEC 4, a22
    GET_UDEC 4, b1
    GET_UDEC 4, b2
    
    mov eax, 0

    mov ebx, 0xffffffff
    and ebx, [a21]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a21]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a21]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a21]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a21]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a22]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    PRINT_UDEC 4, eax
    
    mov eax, 0

    mov ebx, 0xffffffff
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a22]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a22]
    and ebx, [b1]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a21]
    and ebx, [a22]
    and ebx, [b1]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a22]
    and ebx, [b2]
    xor eax, ebx
    
    mov ebx, 0xffffffff
    and ebx, [a11]
    and ebx, [a12]
    and ebx, [a21]
    and ebx, [b2]
    xor eax, ebx

    PRINT_CHAR ' '
    PRINT_UDEC 4, eax
    
    mov eax, 0
    ret
    
    
