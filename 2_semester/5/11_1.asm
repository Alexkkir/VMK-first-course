%include "io.inc"

CEXTERN fscanf
CEXTERN fprintf
CEXTERN fwrite
CEXTERN fclose
CEXTERN strcmp
CEXTERN malloc
CEXTERN strcpy
CEXTERN free
CEXTERN fopen

section .data
    LC0 db "r", 0
    LC1 db "input.txt", 0
    LC2 db "w", 0
    LC3 db "output.txt", 0
    LC4 db "%d%d", 0
    LC5 db "%d", 0
    LC6 db "%d ", 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    
    and esp, 0xfffffff0
    call my_main
    
    mov esp, ebp
    pop ebp
    mov eax, 0
    ret
    

my_main:
        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ebx
        push    ecx
        sub     esp, 64
        mov     eax, esp
        mov     ebx, eax
        sub     esp, 8
        push    LC0
        push    LC1
        call    fopen
        add     esp, 16
        mov     DWORD [ebp-36], eax
        sub     esp, 8
        push    LC2
        push    LC3
        call    fopen
        add     esp, 16
        mov     DWORD [ebp-40], eax
        lea     eax, [ebp-56]
        push    eax
        lea     eax, [ebp-52]
        push    eax
        push    LC4
        push    DWORD [ebp-36]
        call    fscanf
        add     esp, 16
        mov     eax, DWORD [ebp-52]
        add     eax, 1
        lea     edx, [eax-1]
        mov     DWORD [ebp-44], edx
        lea     edx, [0+eax*8]
        mov     eax, 16
        sub     eax, 1
        add     eax, edx
        mov     ecx, 16
        mov     edx, 0
        div     ecx
        imul    eax, eax, 16
        sub     esp, eax
        mov     eax, esp
        add     eax, 3
        shr     eax, 2
        sal     eax, 2
        mov     DWORD [ebp-48], eax
        mov     DWORD [ebp-20], 1
        mov     eax, DWORD [ebp-52]
        mov     DWORD [ebp-16], eax
        mov     DWORD [ebp-12], 1
        jmp     .L2
.L6:
        cmp     DWORD [ebp-12], 1
        jne     .L3
        mov     ecx, DWORD [ebp-52]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-12]
        mov     DWORD [eax+edx*8], ecx
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-12]
        mov     DWORD [eax+4+edx*8], 2
        jmp     .L4
.L3:
        mov     eax, DWORD [ebp-52]
        cmp     DWORD [ebp-12], eax
        jne     .L5
        mov     eax, DWORD [ebp-52]
        lea     ecx, [eax-1]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-12]
        mov     DWORD [eax+edx*8], ecx
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-12]
        mov     DWORD [eax+4+edx*8], 1
        jmp     .L4
.L5:
        mov     eax, DWORD [ebp-12]
        lea     ecx, [eax-1]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-12]
        mov     DWORD [eax+edx*8], ecx
        mov     eax, DWORD [ebp-12]
        lea     ecx, [eax+1]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-12]
        mov     DWORD [eax+4+edx*8], ecx
.L4:
        add     DWORD [ebp-12], 1
.L2:
        mov     eax, DWORD [ebp-52]
        cmp     DWORD [ebp-12], eax
        jle     .L6
        mov     DWORD [ebp-24], 0
        jmp     .L7
.L10:
        lea     eax, [ebp-64]
        push    eax
        lea     eax, [ebp-60]
        push    eax
        push    LC4
        push    DWORD [ebp-36]
        call    fscanf
        add     esp, 16
        mov     eax, DWORD [ebp-60]
        cmp     DWORD [ebp-20], eax
        je      .L8
        mov     eax, DWORD [ebp-64]
        cmp     DWORD [ebp-16], eax
        je      .L9
        mov     ecx, DWORD [ebp-64]
        mov     edx, DWORD [ebp-60]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [eax+edx*8]
        mov     eax, DWORD [ebp-48]
        mov     ecx, DWORD [eax+4+ecx*8]
        mov     eax, DWORD [ebp-48]
        mov     DWORD [eax+4+edx*8], ecx
        mov     ecx, DWORD [ebp-60]
        mov     edx, DWORD [ebp-64]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [eax+4+edx*8]
        mov     eax, DWORD [ebp-48]
        mov     ecx, DWORD [eax+ecx*8]
        mov     eax, DWORD [ebp-48]
        mov     DWORD [eax+edx*8], ecx
        mov     edx, DWORD [ebp-64]
        mov     eax, DWORD [ebp-48]
        mov     ecx, DWORD [ebp-20]
        mov     DWORD [eax+4+edx*8], ecx
        mov     ecx, DWORD [ebp-64]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-20]
        mov     DWORD [eax+edx*8], ecx
        mov     edx, DWORD [ebp-60]
        mov     eax, DWORD [ebp-48]
        mov     ecx, DWORD [ebp-16]
        mov     DWORD [eax+edx*8], ecx
        mov     ecx, DWORD [ebp-60]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-16]
        mov     DWORD [eax+4+edx*8], ecx
        mov     eax, DWORD [ebp-60]
        mov     DWORD [ebp-20], eax
        jmp     .L8
.L9:
        mov     edx, DWORD [ebp-64]
        mov     eax, DWORD [ebp-48]
        mov     ecx, DWORD [ebp-20]
        mov     DWORD [eax+4+edx*8], ecx
        mov     ecx, DWORD [ebp-64]
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-20]
        mov     DWORD [eax+edx*8], ecx
        mov     edx, DWORD [ebp-60]
        mov     eax, DWORD [ebp-48]
        mov     eax, DWORD [eax+edx*8]
        mov     DWORD [ebp-16], eax
        mov     eax, DWORD [ebp-60]
        mov     DWORD [ebp-20], eax
.L8:
        add     DWORD [ebp-24], 1
.L7:
        mov     eax, DWORD [ebp-56]
        cmp     DWORD [ebp-24], eax
        jl      .L10
        mov     eax, DWORD [ebp-20]
        mov     DWORD [ebp-28], eax
        mov     DWORD [ebp-32], 0
        jmp     .L11
.L14:
        mov     eax, DWORD [ebp-52]
        cmp     DWORD [ebp-32], eax
        jne     .L12
        mov     eax, LC5
        jmp     .L13
.L12:
        mov     eax, LC6
.L13:
        sub     esp, 4
        push    DWORD [ebp-28]
        push    eax
        push    DWORD [ebp-40]
        call    fprintf
        add     esp, 16
        mov     eax, DWORD [ebp-48]
        mov     edx, DWORD [ebp-28]
        mov     eax, DWORD [eax+4+edx*8]
        mov     DWORD [ebp-28], eax
        add     DWORD [ebp-32], 1
.L11:
        mov     eax, DWORD [ebp-52]
        cmp     DWORD [ebp-32], eax
        jl      .L14
        sub     esp, 12
        push    DWORD [ebp-36]
        call    fclose
        add     esp, 16
        sub     esp, 12
        push    DWORD [ebp-40]
        call    fclose
        add     esp, 16
        mov     esp, ebx
        mov     eax, 0
        lea     esp, [ebp-8]
        pop     ecx
        pop     ebx
        pop     ebp
        lea     esp, [ecx-4]
        ret