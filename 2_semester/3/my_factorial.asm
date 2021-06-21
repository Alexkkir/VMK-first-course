%include "io.inc"
section .bss
    n resd 1
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    mov [n], dword 4
    mov ecx, 0
    %ifdef COMMENT
    PRINT_STRING 'esp before: '
    PRINT_DEC 4, esp
    NEWLINE
    %endif

    .cyc:
        push ecx
        
        call fact
        call print_eax
        
        pop ecx
        
        inc ecx
        cmp ecx, [n]
        jle .cyc
    
    %ifdef COMMENT
    PRINT_STRING 'esp after: '
    PRINT_DEC 4, esp
    NEWLINE
    PRINT_STRING `\nesp hasn't changed,\nhence, program works\ncorrectly`
    %endif
    xor eax, eax
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