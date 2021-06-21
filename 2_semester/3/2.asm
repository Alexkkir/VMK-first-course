%include "io.inc"
section .bss
    x_p resd 1
    x_c resd 1
    n resd 1
    max_l resd 1
    cur_l resd 1
    
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_UDEC 4, eax
    dec eax
    mov [n], eax
    
    mov eax, [n]
    mov ebx, 0
    cmp eax, ebx
    je .n_eq_1
    GET_DEC 4, x_p
    
    mov eax, 0
    mov [max_l], eax
    mov eax, 1
    mov [cur_l], eax
    
.loop:
    ; n--
    mov eax, [n]
    dec eax
    mov [n], eax
    
    ;scanf(x_c)
    ;if x_p >= x_c
    ;   jump .reset
    ;else
    ;   cur_l++
    ;   x_p = x_c
    GET_DEC 4, x_c
    mov eax, [x_p]
    mov ebx, [x_c]
    cmp eax, ebx
    jge .reset ; монотонность прекратилась
    ; монотонность продолжается
    mov ecx, [cur_l]
    inc ecx
    mov [cur_l], ecx
    jmp .end_of_loop
    
.reset:
    mov eax, [cur_l]
    mov ebx, [max_l]
    cmp eax, ebx
    jg .new_max ;новый максимум
    ; нет, не новый максимум
    mov eax, 1
    mov [cur_l], eax
    jmp .end_of_loop
 
.new_max:
    mov eax, [cur_l]
    mov [max_l], eax
    mov eax, 1
    mov [cur_l], eax
    jmp .end_of_loop

.end_of_loop:
    mov ebx, [x_c]
    mov [x_p], ebx
    mov eax, [n]
    cmp eax, 0
    jg .loop
    mov eax, [cur_l]
    mov ebx, [max_l]
    cmp eax, ebx
    jl .end
    mov [max_l], eax    
    
.end:
    mov eax, [max_l]
    PRINT_UDEC 4, eax
    mov eax, 0
    ret

.n_eq_1:
    PRINT_DEC 1, 1
    mov eax, 0
    ret
    

    
    
    
    
    