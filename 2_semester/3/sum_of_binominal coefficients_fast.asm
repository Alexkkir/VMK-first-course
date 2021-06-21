%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;write your code here
    mov eax, 0 ;k
    push eax
    mov eax, 7 ;l
    push eax
    
    call sum_bc_fast
    
    PRINT_DEC 4, eax
    pop eax
    pop eax
    
    xor eax, eax
    ret
 
sum_bc_fast:
    enter 0, 0
    mov ebx, [ebp + 12] ; k
    mov ecx, [ebp + 8]  ; l
    
    
    
   ; sum = C_{k}^k + C_{k+1}^k + ... + C_{l-1}^k = 
   ; = SUM_{k = 0, l - 1} C_m_k - SUM_{k = 0, k - 1} C_m_k
   ; SUM = C_{n + 1}^{k + 1}
   ; sum = C_l_{k + 1} - C_k_{k + 1} = C_l_{k + 1}
   
   mov eax, 0
   inc ebx
   push ebx
   push ecx
   call bin_coeff
   pop ecx
   pop ebx
   
   leave
   ret
   
bin_coeff:
    enter 0, 0
    mov ebx, [ebp + 12] ; k
    mov ecx, [ebp + 8] ; n
    
    
    
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

print_eax:
    enter 0, 0
    PRINT_DEC 4, eax
    NEWLINE
    leave
    ret
   
    
    

