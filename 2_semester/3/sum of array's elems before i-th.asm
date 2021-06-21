%include "io.inc"

section .bss
    n resd 1
    A resd 100
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, [n]
    
    mov esi, 0
    input:
        GET_DEC 4, eax
        mov dword[A + 4 * esi], eax
        inc esi
        cmp esi, [n]
        jl input
    
    mov esi, 0
    cyc:
        ;sub esp, 4
        ;mov [esp], esi
        push esi
        
        call fun
        
        inc esi
        cmp esi, [n]
        ;pop esi
        
        jl cyc
    mov eax, 0
    
    mov esp, ebp
    pop ebp
    ret
    ret
    
fun:
    enter 0, 0
    
    mov edi, [ebp + 8]
    
    mov esi, 0
    mov eax, 0
    .cyc:
        add eax, dword [A + 4 * esi]
        
        inc esi
        cmp esi, edi
        jle .cyc
    
    call print_eax
    mov esi, [ebp + 8]
    
    leave
    ret
    
 print_eax:
    push ebp
    mov ebp, esp
    
    PRINT_DEC 4, eax
    PRINT_CHAR ' '
    
    pop ebp
    ret   
    