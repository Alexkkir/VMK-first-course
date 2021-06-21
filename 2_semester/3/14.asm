%include "io.inc"

section .bss
    x resd 1
    k resd 1
    len resd 1
    len1 resd 1
    sum_fact resd 1
    oneL resd 1
    

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, [x]
    GET_DEC 4, [k]
    cmp [x], dword 1
    jle trivial_case_ans_0
    
    call calc_len_x
    mov [len], eax
    
    ;PRINT_STRING 'len = '
    ;PRINT_DEC 4, [len]
    ;NEWLINE
    
    mov eax, [k]
    mov ebx, [len]
    cmp eax, ebx
    jg .skip_factorials
    
    ;первый этап: считаем сумму факториалов
    push eax
    push ebx
    call sum_of_bc_fast
    mov [sum_fact], eax
    pop ebx
    pop ebx
    
    ;PRINT_STRING 'sum_fact = '
    ;PRINT_DEC 4, [sum_fact]
    ;NEWLINE
    
    .skip_factorials:
    ;второй этап: инициализируем первое число
    call calc_1L
    mov [oneL], eax
    
    ;PRINT_STRING 'oneL = '
    ;PRINT_DEC 4, [oneL]
    ;NEWLINE
    
    ;перебираем
    call enum_nums
    
    ;PRINT_STRING 'enum = '
    ;PRINT_DEC 4, eax
    ;NEWLINE
    
    add eax, [sum_fact]
    
    ;PRINT_STRING 'ans = '
    PRINT_DEC 4, eax
    
    mov eax, 0
    ret
    
calc_len_x:
    enter 0, 0
    mov eax, 32
    mov ebx, [x]
    .cyc:
        mov ecx, 1
        rol ebx, 1
        and ecx, ebx
        
        dec eax
        cmp ecx, 1
        jne .cyc
    leave
    ret
    
trivial_case_ans_0:
    PRINT_STRING '0'
    jmp end
       
sum_of_bc_fast:
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
   
calc_sum_fact: 
    enter 0, 0
    mov eax, [k]
    mov [len1], eax
    
    mov [sum_fact], dword 0
    
    
    mov ebx, [len]
    cmp eax, ebx
    je .end
    .cyc:
        mov eax, [k]
        push eax
        mov eax, [len1]
        push eax
        
        call bin_coeff
        ;PRINT_STRING `bc: `
        ;call print_eax
        
        add [sum_fact], eax
        
        pop eax
        pop eax
        
        inc dword [len1]
        mov eax, [len1]
        mov ebx, [len]
        cmp eax, ebx
        jl .cyc
    .end:
    leave
    ret
    
  ; sum = C_{k}^k + C_{k+1}^k + ... + C_{l-1}^k

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

calc_1L:
    enter 0, 0
    mov eax, 1
    mov ecx, [len]
    .cyc:
        shl eax, 1
        dec ecx
        cmp ecx, 0
        jg .cyc
    leave
    ret
    
enum_nums:
    enter 0, 0
    mov ecx, [oneL]
    mov eax, 0
    .cyc:
        push eax
        push ecx
        call are_there_k_zeros
        pop ecx
        pop ebx
        add eax, ebx
        
        inc ecx
        mov edx, [x]
        cmp ecx, edx
        jle .cyc
    leave
    ret
    
are_there_k_zeros:
    enter 0, 0
    push dword [ebp + 12]
    push dword [ebp + 8]
    call calc_quantity_of_zeros
    pop edx
    pop edx
    
    mov edx, 0
    mov ebx, [k]
    cmp eax, ebx
    jne .end
    mov edx, 1
    
    .end:
    mov eax, edx
    leave
    ret
        
    
calc_quantity_of_zeros:
    enter 0, 0
    mov ebx, [ebp + 8]
    mov eax, 0
    mov ecx, 0
    .cyc:
        mov edx, 1
        and edx, ebx
        cmp edx, 0
        jne .end
        inc eax
        
        .end:
        shr ebx, 1
        inc ecx
        
        mov edx, [len]
        cmp ecx, edx
        jl .cyc
    leave
    ret
        
end:
    mov eax, 0
    ret
    
    %ifdef COMMENT
    1
    1 0
    1 1
    1 0 0
    1 0 1
    1 1 0
    1 1 1
    1 0 0 0
    1 0 0 1
    1 0 1 0
    1 0 1 1
    1 1 0 0
    1 1 0 1
    1 1 1 0
    1 1 1 1
    -- дальше перебором
    1 0 0 0 0
    1 0 0 0 1
    1 0 0 1 0
    C_3^3, C_4^3
    ===
    1 C_0^0 = 1
      C_1^0 = 1
      C_0^1
    11 C_1^0 = 1
    111
    1111
    1.1111
    11.1111
    111.1111
    1111.1111 
    дальше перебором 
    256-10000.0000  
    
    C_n^k, n-k - маленькая
    С
    
    %endif
    
    
