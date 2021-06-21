%include "io.inc"
section .bss
    n resd 1
    k resd 1
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    mov [n], dword 10
    mov ecx, 0

    .cyc:
        push ecx
        mov eax, [n]
        push eax
        
        call bin_coeff
        call print_eax
        
        pop ecx
        pop ecx
        
        inc ecx
        cmp ecx, [n]
        jle .cyc
        
    xor eax, eax
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