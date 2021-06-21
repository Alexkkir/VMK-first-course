%include "io.inc"

section .bss
    n equ 5
    m equ 10
    arr resb n
    arr2 resb m
    
section .text
global CMAIN
CMAIN:
    ;write your code here
    mov edi, arr
    mov ecx, n
    mov al, 'A'
    PRINT_CHAR al
    PRINT_STRING `\n`
    call fill_mem
    
    mov edi, arr2
    mov ecx, m
    mov al, 'B'
    PRINT_CHAR al
    PRINT_STRING `\n`
    call fill_mem
    
fill_mem:
    jecxz fm_q
fm_lp:
    mov [edi], al
    inc edi
    loop fm_lp
fm_q:
    ret

    