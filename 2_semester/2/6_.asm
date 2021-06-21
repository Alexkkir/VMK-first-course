%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov eax, 0 ;n
    mov ebx, 0 ;k 
    mov ecx, 0 ;1...1^k
    mov edx, 0 ;i
    
    GET_UDEC 4, eax
    GET_UDEC 4, ebx
    
    mov edx, ebx
    
    jmp .loop
  .loop:
    shl ecx, 1
    inc ecx
    dec edx
    cmp edx, 0
    jne .loop
  .print
    and eax, ecx
    PRINT_UDEC 4, eax
    mov eax, 0
    ret
    