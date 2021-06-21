%include "io.inc"


section .text
global CMAIN
CMAIN:
    ;write your code here
    
    call rec
    
    xor eax, eax
    ret
    
rec:
    enter 0, 0
    GET_DEC 4, eax
    cmp eax, 0
    je .stop
    push eax
    call rec
    pop eax
    call print_eax
    
    .stop:
    leave
    ret
    
print_eax:
    enter 0, 0
    PRINT_DEC 4, eax
    PRINT_STRING ' '
    leave
    ret
    