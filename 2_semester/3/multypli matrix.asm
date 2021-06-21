%include "io.inc"

section .bss
    size equ 100
    A resd (size * size)
    B resd (size * size)
    C resd (size * size)
    
    n resd 1
    m resd 1
    k resd 1
    
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, [n]
    GET_DEC 4, [m]
    GET_DEC 4, [k]
    
    ;mov dword[A], 1
    ;mov dword[A + 4], 0
    ;mov dword[A + 8], 0
    ;mov dword[A + 12], 1
    
    ;mov dword[B], 1
    ;mov dword[B + 4], 2
    ;mov dword[B + 8], 3
    ;mov dword[B + 12], 4
    call input_A
    call input_B
    
    call calc_C
    
    call print_C
    
    mov eax, 0
    ret
    
    
calc_C:
    push ebp
    mov ebp, esp
    
    mov esi, 0
    .cyc1:
        mov edi, 0
        .cyc2:
            sub esp, 8
            mov [esp], esi
            mov [esp + 4], edi
            
            call calc_elem_of_C
            
            mov ecx, esi
            mov ebx, [k]
            imul ecx, ebx
            add ecx, edi
            mov dword [C + 4 * ecx], eax
            
            inc edi
            cmp edi, [k]
            jl .cyc2
        inc esi
        cmp esi, [n]
        jl .cyc1
    mov esp, ebp
    pop ebp
    ret

calc_elem_of_C:
    push ebp
    mov ebp, esp
    
    mov eax, 0
    mov esi, 0
    .cyc:
        mov edx, 0
        
        mov ecx, [ebp + 8]
        mov ebx, [m]
        imul ecx, ebx
        add ecx, esi
        
        mov edx, dword [A + 4 * ecx]
        
        mov ecx, esi
        mov ebx, [k]
        imul ecx, ebx
        add ecx, [ebp + 12]
        
        imul edx, dword [B + 4 * ecx]
        add eax, edx
        
        inc esi
        cmp esi, [m]
        jl .cyc        
    
    mov esi, [ebp + 8]
    mov edi, [ebp + 12]
    mov esp, ebp
    pop ebp
    ret

input_A:
    push ebp
    mov ebp, esp
    mov esi, 0
    .cyc1:
        mov edi, 0
        .cyc2:
            mov ecx, esi
            mov eax, [m]
            imul ecx, eax
            add ecx, edi
            
            GET_DEC 4, eax
            mov dword [A + 4 * ecx], eax
            
            inc edi
            cmp edi, [m]
            jl .cyc2
        inc esi
        cmp esi, [n]
        jl .cyc1
    mov esp, ebp
    pop ebp
    ret

input_B:
    push ebp
    mov ebp, esp
    mov esi, 0
    .cyc1:
        mov edi, 0
        .cyc2:
            mov ecx, esi
            mov eax, [k]
            imul ecx, eax
            add ecx, edi
            
            GET_DEC 4, eax
            mov dword [B + 4 * ecx], eax
            
            inc edi
            cmp edi, [k]
            jl .cyc2
        inc esi
        cmp esi, [m]
        jl .cyc1
    mov esp, ebp
    pop ebp
    ret
        
print_A:
    push ebp
    mov ebp, esp
    
    mov esi, 0
    .cyc1:
        mov edi, 0
        .cyc2:
            mov ecx, esi
            mov eax, [m]
            imul ecx, eax
            add ecx, edi
            
            mov eax, dword [A + 4 * ecx]
            call print_eax
            
            inc edi
            cmp edi, [m]
            jl .cyc2
        NEWLINE
        inc esi
        cmp esi, [n]
        jl .cyc1
    pop ebp
    ret
                
print_B:
    push ebp
    mov ebp, esp
    
    mov esi, 0
    .cyc1:
        mov edi, 0
        .cyc2:
            mov ecx, esi
            mov eax, [k]
            imul ecx, eax
            add ecx, edi
            
            mov eax, dword [B + 4 * ecx]
            call print_eax
            
            inc edi
            cmp edi, [k]
            jl .cyc2
        NEWLINE
        inc esi
        cmp esi, [m]
        jl .cyc1
    mov esp, ebp
    pop ebp
    ret 

print_C:
    push ebp
    mov ebp, esp
    
    mov esi, 0
    .cyc1:
        mov edi, 0
        .cyc2:
            mov ecx, esi
            mov eax, [k]
            imul ecx, eax
            add ecx, edi
            
            mov eax, dword [C + 4 * ecx]
            call print_eax
            
            inc edi
            cmp edi, [k]
            jl .cyc2
        NEWLINE
        inc esi
        cmp esi, [n]
        jl .cyc1
    mov esp, ebp
    pop ebp
    ret 

print_eax:
    push ebp
    mov ebp, esp
    
    PRINT_DEC 4, eax
    PRINT_CHAR ' '
    
    pop ebp
    ret
