%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;write your code here
    PRINT_STRING 'Hellow, guys'
    
    xor eax, eax
    ret