%include "io.inc"

CEXTERN malloc
CEXTERN fopen
CEXTERN printf
CEXTERN fscanf
CEXTERN fclose
CEXTERN feof
CEXTERN fread

section .data
    stack_p dd 0
    tmp dd 0
    root dd 0
    n dd 0
    
    f1 dd 0
    f1_txt db "input.bin", 0
    ; f1_txt db "C:\Users\1\Documents\EVM\2_semester\5\input2.bin", 0
    rb db "rb", 0
    
    key dd 0
    left dd 0
    right dd 0
    
    ok dd 1
    
    d db `%d `, 0
    

section .rodata

section .text
global CMAIN
CMAIN:
    ;write your code here
    push ebp
    mov ebp, esp
        
    and esp, 0xfffffff0
    sub esp, 12
    push 40000
    call malloc
    
    mov dword [stack_p], eax
    mov dword [tmp], eax
    
    ; fopen
    add esp, 8
    push rb
    push f1_txt
    call fopen
    mov dword [f1], eax
    
    
    part_1:
    ; feof
    add esp, 4
    push dword [f1]
    call feof
    cmp eax, 0
   
    jne part_2
    
        
    ; key
    add esp, 16
    push dword [f1]
    push dword 1
    push dword 4
    push dword key
    call fread
        
    ; left
    add esp, 16
    push dword [f1]
    push dword 1
    push dword 4
    push dword left
    call fread
        
    ; right
    add esp, 16
    push dword [f1]
    push dword 1
    push dword 4
    push dword right
    call fread
       
    ; saving
    mov eax, dword [key]
    mov ebx, dword [tmp]
    mov dword [ebx], eax
    
    mov eax, dword [left]
    mov ebx, dword [tmp]
    add ebx, 4
    mov dword [ebx], eax
    
    mov eax, dword [right]
    mov ebx, dword [tmp]
    add ebx, 8
    mov dword [ebx], eax
    
    add dword [tmp], 12
    inc dword [n]
    jmp part_1
    
    part_2:
    dec dword [n]
        
    mov eax, dword [stack_p]
    mov dword [root], eax
    
    do1:
        ; является ли узел root вершиной?
        mov dword [ok], 1
        
        mov ecx, dword [n]
        mov eax, dword [stack_p]
        mov dword [tmp], eax
        for1:
            mov eax, dword [tmp]
            add eax, 4
            mov edx, dword [eax] ; в edx - смещение
            cmp edx, -1
            je .skip1
            
            mov eax, dword [stack_p]
            add eax, edx ; eax = tmp->left                        

            mov ebx, dword [root]
            cmp eax, ebx
            je .change_root
            
            .skip1:
            mov eax, dword [tmp]
            add eax, 8
            mov edx, dword [eax] ; в edx - смещение
            
            cmp edx, -1
            je .skip2
            
            mov eax, dword [stack_p]
            add eax, edx ; eax = tmp->left                        

            mov ebx, dword [root]
            cmp eax, ebx
            je .change_root
            
            .skip2:
            jmp .end_for
            
            .change_root:
            mov eax, dword [tmp]
            mov dword [root], eax
            mov dword [ok], 0
            
        .end_for: 
        dec ecx
        add dword [tmp], 12
        
        cmp ecx, 0
        jg for1
        
    while1:
        mov eax, dword [ok]
        cmp eax, 1
        jne do1 ; вершина не найдена
        
        
        
    part_3:
    and esp, 0xfffffff0
    add esp, 4
    push dword [root]
    call print_tree
    
    
    leave    
    xor eax, eax
    ret
    
    
print_tree:
    push ebp
    mov ebp, esp
        
    and esp, 0xfffffff0
    add esp, 8
    
    mov eax, dword [ebp + 8]
    mov ebx, dword [eax]
    
    push ebx
    push d
    call printf
    
    mov eax, dword [ebp + 8]    
    add esp, 4
    mov ebx, dword [eax + 4]
    cmp ebx, -1
    je .skip1
    
    mov ecx, dword [stack_p]
    add ecx, ebx
    push ecx
    call print_tree
    
    .skip1:
    mov eax, dword [ebp + 8]    
    add esp, 4
    mov ebx, dword [eax + 8]
    cmp ebx, -1
    je .skip2
    
    mov ecx, dword [stack_p]
    add ecx, ebx
    push ecx
    call print_tree
    
    .skip2:
    leave
    ret

    
; вспомогательные функции -------------------------------------
print_eax_addr:
    PRINT_DEC 4, [eax]
    PRINT_STRING " "
    ret
    
print_eax:
    PRINT_DEC 4, eax
    ret
    
print_stack:
    mov ecx, dword [n]
    imul ecx, 3
    mov eax, dword [stack_p]
    .while:
    call print_eax_addr
    add eax, 4
    dec ecx
    cmp ecx, 0
    jg .while
    ret
   