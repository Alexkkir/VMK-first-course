%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;write your code here
    PRINT_DEC 4, [esp]
    NEWLINE
    mov eax, 3
    push eax
    mov eax, 6
    push eax
    call bin_coeff
    PRINT_DEC 4, eax
    NEWLINE
    pop eax
    pop eax
    PRINT_DEC 4, [esp]
    xor eax, eax
    ret
    
bin_coeff:
    enter 0, 0
    mov ebx, [ebp + 12]
    mov ecx, [ebp + 8]
    cmp ebx, 0
    jle .ans_is_1
    cmp ebx, ecx
    jg .ans_is_0
    
    ; first call
    mov eax, 0
    
    dec ecx
    push eax
    push ebx
    push ecx
    call bin_coeff
    pop ecx
    pop ebx
    pop edx
    add eax, edx
    
    dec ebx
    push eax
    push ebx
    push ecx
    call bin_coeff
    pop ecx
    pop ebx
    pop edx   
    add eax, edx
    
    leave
    ret
    
    .ans_is_1:
    mov eax, 1
    leave
    ret
    
    .ans_is_0:
    mov eax, 0
    leave
    ret    