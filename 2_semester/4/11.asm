%include "io.inc"

section .data
    sum dd 0
    d dd 0
    sign dd 0
    x dd 0
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_DEC 4, ecx
    .for:
        cmp ecx, 0
        je .endfor
        
        GET_UDEC 4, ebx
        push ebx
        call div3
        pop ebx
        
        .if:
            cmp eax, 0
            jne .false
        .true:
            PRINT_STRING 'YES'
            NEWLINE
            jmp .endif
        .false:
            PRINT_STRING 'NO'
            NEWLINE
            jmp .endif
        .endif:
        dec ecx
        jmp .for
        
    .endfor:    
    xor eax, eax
    ret
    
    
    
div3:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp + 8]
    .while:
        cmp ebx, 3
        jb .endwhile
        
        push ebx
        call calcsum
        mov ebx, eax
        pop eax
        jmp .while
    .endwhile:
    
    mov eax, ebx
    
    leave
    ret

calcsum:
    enter 0, 0
    mov ebx, dword [ebp + 8]
    mov [sum], dword 0
    mov [sign], dword 1
    
    .while:
        cmp ebx, dword 0
        jbe .endwhile
        mov [d], dword 1
        and [d], ebx
        
        mov eax, [sign]
        mov edx, [d]
        imul edx, eax
        mov [d], edx
        
        mov eax, [d]
        add [sum], eax
        
        mov eax, [sign]
        .if:
            cmp eax, dword 1
            jne .false
        .true:
            mov [sign], dword 2
            jmp .endif
        .false:
            mov [sign], dword 1
            jmp .endif
        .endif:        
        
        shr ebx, 1
        jmp .while
        
    .endwhile:
    
    mov eax, [sum]
    
    .while2:
    cmp eax, 3
    jl .endwhile2
    sub eax, 3
    jmp .while2
    .endwhile2:
    
    leave
    ret   
    
    
    
