%include "io.inc"
section .bss
    len1 resd 1
    k resd 1
    len resd 1
    sum_fact resd 1
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    mov [k], dword 0
    mov [len], dword 8
    call calc_sum_fact
    PRINT_DEC 4, [sum_fact]
    
    mov eax, 0
    ret
    
calc_sum_fact: 
    enter 0, 0
    mov eax, [k]
    mov [len1], eax
    
    mov [sum_fact], dword 0
    
    cmp eax, 0
    jne .continue
    inc dword [len1]
    .continue:
    
    mov ebx, [len]
    cmp eax, ebx
    je .end
    .cyc
        mov eax, [k]
        push eax
        mov eax, [len1]
        push eax
        
        call bin_coeff
        add [sum_fact], eax
        call print_eax
        mov eax, [len1]
        call print_eax
        NEWLINE
        
        
        pop eax
        pop eax
        
        inc dword [len1]
        mov eax, [len1]
        mov ebx, [len]
        cmp eax, ebx
        jle .cyc
    .end:
    leave
    ret

bin_coeff:
    enter 0, 0
    ;ecx - для знаменателя
    
    mov ebx, [ebp + 12] ; k
    push ebx
    call fact ; k!
    pop ebx
    mov ecx, eax
    
    mov ebx, [ebp + 12] ; k
    mov edx, [ebp + 8] ; n
    sub edx, ebx
    push edx
    call fact ; (n-k)!
    pop edx
    imul ecx, eax
    
    mov ebx, [ebp + 8]
    push ebx
    call fact ; n! ; n! now is in eax
    pop ebx
    
    mov edx, 0
    cdq  
    div ecx ;coeff in eax
    
    leave
    ret
    
fact:
    enter 0, 0
    mov ebx, [ebp + 8]
    mov eax, 1
    cmp ebx, 0
    jle .end
    .cyc:
        imul eax, ebx
        dec ebx
        cmp ebx, 0
        jg .cyc
    .end:
    leave
    ret
    
print_eax:
    enter 0, 0
    PRINT_DEC 4, eax
    NEWLINE
    leave
    ret