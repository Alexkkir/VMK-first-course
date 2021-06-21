%include "io.inc"

section .data
   
section .bss
    n equ 5
    A resd n

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    input_A:
        mov ecx, 0
        .cyc:
            GET_DEC 4, eax
            mov dword [A+ 4 * ecx], eax
            add ecx, 1
            mov edx, n
            cmp ecx, edx
            jl .cyc
        
     print:
        mov ecx, 0
        .cyc:
            mov eax, dword [A + 4 * ecx]
            call print_eax
            inc ecx
            
            cmp ecx, n
            jl .cyc
            
    mov eax, 0
    ret
            
print_eax:
    push ebp
    mov ebp, esp
    
    PRINT_DEC 4, eax
    
    pop ebp
    ret
    
        
      
        