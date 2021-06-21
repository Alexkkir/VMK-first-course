%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    mov eax, 0 ; d
    mov ebx, 0 ; d_{n-1}
    mov ecx, 0 ; d_{n-2} ... d_{0}
    mov edx, 0 ; answer
    mov ebp, 0 ; running totals
    
    GET_DEC 4, eax
    
    mov ebx, eax
    and ebx, 0x80000000
    
    mov ecx, eax
    sub ecx, ebx
    
    shr ebx,31
    
    mov edx, 0x80000000
    imul edx, ebx
    
    mov ebp, -2
    imul ebp, ebx
    add ebp, 1
    imul ebp, ecx
    add edx, ebp
    PRINT_UDEC 4, edx
    
    mov eax, 0
    ret