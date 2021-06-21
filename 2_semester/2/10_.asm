%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    GET_CHAR al
    GET_CHAR ah
    
    GET_CHAR bl
    GET_CHAR bl
    GET_CHAR bh

    
    sub al, bl
    sub ah, bh
    
    movsx esi, al
    movsx edi, ah
    ;PRINT_DEC 1, esi ;delta x
    ;PRINT_DEC 1, edi ;delta y
    
    ;modul of esi (of x); template from problem 9
    mov eax, 0 ; d
    mov ebx, 0 ; d_{n-1}
    mov ecx, 0 ; d_{n-2} ... d_{0}
    mov edx, 0 ; answer
    mov ebp, 0 ; running totals
    
    mov eax, esi
    
    mov ebx, eax
    and ebx, 0x80000000
    
    mov ecx, eax
    sub ecx, ebx
    
    shr ebx,31
    
    mov edx, 0x80000000
    imul edx, ebx
    
    mov ebp, -2
    imul ebp, ebx
    add ebp, 1
    imul ebp, ecx
    add edx, ebp
    mov esi, edx
    
    ;modul of edy (of y)
    mov eax, 0 ; d
    mov ebx, 0 ; d_{n-1}
    mov ecx, 0 ; d_{n-2} ... d_{0}
    mov edx, 0 ; answer
    mov ebp, 0 ; running totals
    
    mov eax, edi
    
    mov ebx, eax
    and ebx, 0x80000000
    
    mov ecx, eax
    sub ecx, ebx
    
    shr ebx,31
    ;
    mov edx, 0x80000000
    imul edx, ebx
    
    mov ebp, -2
    imul ebp, ebx
    add ebp, 1
    imul ebp, ecx
    add edx, ebp
    mov edi, edx
    
    add esi, edi
    PRINT_DEC 4, esi
    mov eax, 0
    ret
    
    
    
    
    
    