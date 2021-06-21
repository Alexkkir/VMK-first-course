%include "io.inc"

section .bss
a resd 1
b resd 1
c resd 1
d resd 1
n1 resd 1
n2 resd 1
section .text
global CMAIN
CMAIN:
    ;write your code here
    GET_UDEC 4, [a]
    GET_UDEC 4, [b]
    GET_UDEC 4, [c]
    GET_UDEC 4, [d]
    
    push dword [a]
    push dword [b]
    call gcd
    add dword [n1], eax
    pop ebx
    pop ebx
    
    push dword [c]
    push dword [d]
    call gcd
    add dword [n2], eax
    pop ebx
    pop ebx
    
    push dword [n1]
    push dword [n2]
    call gcd
    PRINT_UDEC 4, eax
    pop ebx
    pop ebx
    
    mov eax, 0
    ret
    
gcd:
    enter 0, 0
    mov eax, [ebp + 8]
    mov ebx,[ebp + 12]
        
    .cyc:
    mov edx, 0
    cdq
    div ebx
    mov eax, ebx
    mov ebx, edx
    cmp ebx, 0
    jg .cyc
    
    
    leave
    ret
