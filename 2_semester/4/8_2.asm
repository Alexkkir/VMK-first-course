%include "io.inc"

section .data
 k dd 0
 ans dd 0
 sum dd 0
 
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
;3797882614 4
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_UDEC 4, ecx
    GET_UDEC 4, [k]
    
    add [ans], ecx
    .while:
    cmp ecx, [k]
    jb .endwhile    
        push ecx
        call sum_d
        pop ecx
        
        mov ecx, eax
        add [ans], ecx
        jmp .while
    .endwhile:
    add [ans], ecx
    PRINT_UDEC 4, [ans]
    
    xor eax, eax
    ret
    
sum_d:
    push ebp
    mov ebp, esp
    
    mov eax, [ebp + 8]
    mov [sum], dword 0
    
    .while:
    cmp eax, 0
    je .endwhile
        mov edx, 0
        mov ecx, [k]
        
        div ecx
        add [sum], edx
        jmp .while
    .endwhile:
    mov eax, [sum]
    leave
    ret
    
print_eax:
    push ebp
    mov ebp, esp
    PRINT_DEC 4, eax
    NEWLINE
    leave
    ret
    
    ошибки:
    1) вместо ja/jb использовал jg/jl
    2) использовал cdq при беззнаковом делении
   
    
    
    
    