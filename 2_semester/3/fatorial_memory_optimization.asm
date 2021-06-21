%include "io.inc"

section .bss
k resd 1
len1 resd 1
section .text
global CMAIN
CMAIN:
    ;write your code here
    mov [k], dword 4
    mov [len1], dword 6
    
    mov eax, [k]
    push eax
    mov eax, [len1]
    push eax
    
    call bin_coeff
    call print_eax
    
    pop eax
    pop eax
        
    xor eax, eax
    ret
   
bin_coeff:
    enter 0, 0
    ;ecx - для знаменателя
    
    mov eax, 1
    mov ebx, [ebp + 12] ; k
    mov ecx, [ebp + 8] ; n
    mov edx, ecx
    sub edx, ebx ; n - k
    push edx
    
    .cyc:
    cmp ebx, ecx
    jg .stop
    imul eax, ebx
    inc ebx
    jmp .cyc
    
    .stop:
    mov edx, eax
    call fact
    pop ebx
    
    mov ecx, eax
    mov eax, edx
    mov edx, 0
    cdq
    div ecx
    
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
