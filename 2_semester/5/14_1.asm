%include "io.inc"

CEXTERN calloc
CEXTERN malloc
CEXTERN feof
CEXTERN fopen
CEXTERN fscanf
CEXTERN fprintf
CEXTERN printf

section .rodata
    d db "%d", 0
    d_ db "%d ", 0
    r db "r", 0
    w db "w", 0
    ;input db "input.txt", 0
    ;output db "output.txt", 0
    input db "C:\Users\1\Documents\EVM\2_semester\5\input.txt", 0
    output db "C:\Users\1\Documents\EVM\2_semester\5\output.txt", 0
    
section .data
    i_node dd 0
    j_node dd 0
    i dd 0
    j dd 0
    tmp dd 0
    mid dd 0
    left dd 0
    right dd 0
    f1 dd 0
    f2 dd 0
    n dd 0
    len dd 0
    head dd 0
    tail dd 0
    x dd 0
    p dd 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 16
    
    ; fopen
    add esp, 8
    push r
    push input
    call fopen
    mov dword [f1], eax
        
    add esp, 8
    push w
    push output
    call fopen
    mov dword [f2], eax
    
    ; malloc => head
    add esp, 4
    push 12
    call malloc
    mov dword [head], eax
    mov dword [p], eax
    
    while:
        add esp, 12
        push x
        push d
        push dword [f1]
        call fscanf
        cmp eax, 1
        jne endwhile
            mov eax, dword [x]
            mov ebx, dword [p]
            mov dword[ebx], eax
            inc dword [n]
            
            add esp, 4
            push 12
            call malloc
            call print_eax
            
            mov ebx, dword [p]
            mov dword[ebx + 8], eax
            
            mov ecx, eax
            mov ebx, dword [p]
            mov dword [ecx + 4], ebx
            
            mov dword [p], ecx
            
            
            mov eax, esp
            call print_eax
            mov eax, dword [n]
            call print_eax
            NEWLINE
            jmp while
    endwhile:
    
    mov ebx, dword [p]
    mov ebx, dword [ebx + 4]
    mov dword [tail], ebx
   
    
    add esp, 12
    push dword [n]
    push dword [tail]
    push dword [head]
    call sort
    
    mov eax, dword [head]
    mov dword [p], eax
    while_print:
        mov eax, dword [p]
        mov ebx, dword [tail]
        mov ebx, dword [ebx + 8]
        cmp eax, ebx
        je end_while_print
            mov eax, dword [p]
            mov eax, dword [eax]
            add esp, 12
            push eax
            push d_
            push dword [f2]
            call fprintf
            
            mov eax, dword [p]
            mov eax, dword [eax + 8]
            mov dword [p], eax
            jmp while_print
    end_while_print: 
        
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
    
sort:
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 16    
    
    NEWLINE
    call print_list
    
    mov eax, dword [ebp + 16]
    PRINT_STRING `n: `
    add esp, 8
    push eax
    push d
    call printf
    NEWLINE
    
    mov eax, dword [ebp + 8]
    mov eax, dword [eax]
    PRINT_STRING "head: "
    add esp, 8
    push eax
    push d
    call printf
    NEWLINE
    
    mov eax, dword [ebp + 12]
    mov eax, dword [eax]
    PRINT_STRING "tail: "
    add esp, 8
    push eax
    push d
    call printf
    NEWLINE
    
    ; [ebp + 16] = len
    ; [ebp + 12] = right
    ; [ebp + 8] = left
    
    
    ; finding of element = array[(left + right)/2]
    mov ecx, 0
    mov edx, 0
    mov eax, dword [ebp + 16]
    dec eax
    mov ebx, 2
    div ebx
    mov edx, eax ;edx = (len - 1) / 2
    
    mov eax, dword [ebp + 8]
    mov dword [p], eax
    
    for:
        cmp ecx, edx
        jnl .endfor
            mov ebx, dword [p]
            mov ebx, dword [ebx + 8]
            mov dword [p], ebx
            
            inc ecx
            jmp for
    .endfor:
    mov ebx, dword [p]
    mov ebx, dword [ebx]
    mov dword [mid], ebx
    
    PRINT_STRING "mid: "
    PRINT_DEC 4, [mid]
    NEWLINE
    
    ; main part
    mov eax, dword [ebp + 8]
    mov dword [i_node], eax
    
    mov eax, dword [ebp + 12]
    mov dword [j_node], eax
    
    mov dword [i], 0
    
    mov eax, dword [ebp + 16]
    dec eax
    mov dword [j], eax
    
    while_main:
        mov eax, dword [i]
        mov ebx, dword [j]
        cmp eax, ebx
        jnle end_while_main
            while_i:                
                mov eax, dword [i_node]
                mov eax, dword [eax]
                mov ebx, dword [mid]
                cmp eax, ebx
                jnl end_while_i
                
                mov eax, dword [i]
                mov ebx, dword [ebp + 16]
                dec ebx
                cmp eax, ebx
                jnl end_while_i
                    inc dword [i]
                    mov eax, dword [i_node]
                    mov eax, dword [eax + 8]
                    mov dword [i_node], eax
                    jmp while_i
            end_while_i:
            
            while_j:                
                mov eax, dword [j_node]
                mov eax, dword [eax]
                mov ebx, dword [mid]
                cmp eax, ebx
                jng end_while_j
                
                mov eax, dword [j]
                mov ebx, 0
                cmp eax, ebx
                jng end_while_j
                    dec dword [j]
                    mov eax, dword [j_node]
                    mov eax, dword [eax + 4]
                    mov dword [j_node], eax
                    jmp while_j
            end_while_j:
            
            ; swap, if i <= j
            mov eax, dword [i]
            mov ebx, dword [j]
            cmp eax, ebx
            jnle endif
                mov eax, dword [i_node]
                mov edx, dword [eax]  ; edx = i_node->val
               
                
                mov eax, dword [j_node]
                mov ebx, dword [eax] ;ebx = j_node->val
                
                mov eax, dword [i_node]
                mov dword [eax], ebx ;i_node->val = j_node->val
                
                mov eax, dword [j_node]
                mov dword [eax], edx ;j_node = i_node
                
                ; bias
                inc dword [i]
                mov eax, dword [i_node]
                mov eax, dword [eax + 8]
                mov dword [i_node], eax
                
                dec dword [j]
                mov eax, dword [j_node]
                mov eax, dword [eax + 4]
                mov dword [j_node], eax
            endif:
            jmp while_main                
    end_while_main:          
    
    mov eax, dword [i_node]
    mov dword [ebp -4], eax
    mov eax, dword [i]
    mov dword [ebp - 8], eax
    
    cmp dword [j], 0
    jng skip_rec_1
        add esp, 12
        mov eax, dword [j]
        inc eax
        push eax
        push dword [j_node]
        push dword [ebp + 8]
        call sort
    skip_rec_1:
    
    mov eax, dword [ebp - 4]
    mov dword [i_node], eax
    mov eax, dword [ebp - 8]
    mov dword [i], eax
    
    mov eax, dword [ebp + 16]
    dec eax
    cmp dword [i], eax
    jnl skip_rec_2
        add esp, 12
        mov eax, dword [ebp + 16]
        mov ebx, dword [i]
        sub eax, ebx
        push eax
        push dword [ebp + 12]
        push dword [i_node]
        call sort
    skip_rec_2:
    
    mov esp, ebp
    pop ebp
    ret
    
print_list:
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 16
    
    mov eax, dword [head]
    mov dword [p], eax
    _while_print:
        mov eax, dword [p]
        mov ebx, dword [tail]
        mov ebx, dword [ebx + 8]
        cmp eax, ebx
        je _end_while_print
            mov eax, dword [p]
            mov eax, dword [eax]
            add esp, 8
            push eax
            push d_
            call printf
            
            mov eax, dword [p]
            mov eax, dword [eax + 8]
            mov dword [p], eax
            jmp _while_print
    _end_while_print: 
    
    NEWLINE
        
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret 
    
print_eax:
    PRINT_DEC 4, eax
    NEWLINE
    ret
    