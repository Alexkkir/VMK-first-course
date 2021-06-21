%include "io.inc"
section .data
    card dw '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' 
    mast dw 'S', 'C', 'D', 'H'
section .text   
global CMAIN
CMAIN:
    ;PRINT_STRING [card + 0]
    ;NEWLINE
    GET_UDEC 4, eax
    
    dec eax
    
    mov edx, 0
    mov ecx, 13
    cdq
    div ecx
    
       
    
    imul edx, 2
    
    imul eax, 2

    PRINT_STRING [card + edx]
    PRINT_STRING [mast + eax] 
    mov eax, 0
    ret