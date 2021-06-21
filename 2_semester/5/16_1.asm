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
    LC4 db "%d", 0
    LC5 db "%s%u", 0
    LC6 db "%s", 0
    LC7 db `%u\n`, 0
    LC8 db `-1\n`, 0
    

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

height:
        push    ebp
        mov     ebp, esp
        cmp     DWORD [ebp+8], 0
        je      .L2
        mov     eax, DWORD [ebp+8]
        movzx   eax, BYTE [eax+108]
        jmp     .L4
.L2:
        mov     eax, 0
.L4:
        pop     ebp
        ret
is_first_bigger_than_second:
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        sub     esp, 8
        push    DWORD [ebp+12]
        push    DWORD [ebp+8]
        call    strcmp
        add     esp, 16
        test    eax, eax
        setg    al
        movzx   eax, al
        leave
        ret
bfactor:
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        push    eax
        call    height
        add     esp, 4
        movzx   ebx, al
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        push    eax
        call    height
        add     esp, 4
        movzx   edx, al
        mov     eax, ebx
        sub     eax, edx
        mov     ebx, DWORD [ebp-4]
        leave
        ret
fixheight:
        push    ebp
        mov     ebp, esp
        sub     esp, 16
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        push    eax
        call    height
        add     esp, 4
        mov     BYTE [ebp-1], al
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        push    eax
        call    height
        add     esp, 4
        mov     BYTE [ebp-2], al
        movzx   edx, BYTE [ebp-2]
        movzx   eax, BYTE [ebp-1]
        cmp     dl, al
        cmovnb  eax, edx
        lea     edx, [eax+1]
        mov     eax, DWORD [ebp+8]
        mov     BYTE [eax+108], dl
        nop
        leave
        ret
rotateright:
        push    ebp
        mov     ebp, esp
        sub     esp, 16
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        mov     DWORD [ebp-4], eax
        mov     eax, DWORD [ebp-4]
        mov     edx, DWORD [eax+116]
        mov     eax, DWORD [ebp+8]
        mov     DWORD [eax+112], edx
        mov     eax, DWORD [ebp-4]
        mov     edx, DWORD [ebp+8]
        mov     DWORD [eax+116], edx
        push    DWORD [ebp+8]
        call    fixheight
        add     esp, 4
        push    DWORD [ebp-4]
        call    fixheight
        add     esp, 4
        mov     eax, DWORD [ebp-4]
        leave
        ret
rotateleft:
        push    ebp
        mov     ebp, esp
        sub     esp, 16
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        mov     DWORD [ebp-4], eax
        mov     eax, DWORD [ebp-4]
        mov     edx, DWORD [eax+112]
        mov     eax, DWORD [ebp+8]
        mov     DWORD [eax+116], edx
        mov     eax, DWORD [ebp-4]
        mov     edx, DWORD [ebp+8]
        mov     DWORD [eax+112], edx
        push    DWORD [ebp+8]
        call    fixheight
        add     esp, 4
        push    DWORD [ebp-4]
        call    fixheight
        add     esp, 4
        mov     eax, DWORD [ebp-4]
        leave
        ret
balance:
        push    ebp
        mov     ebp, esp
        push    DWORD [ebp+8]
        call    fixheight
        add     esp, 4
        push    DWORD [ebp+8]
        call    bfactor
        add     esp, 4
        cmp     eax, 2
        jne     .L15
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        push    eax
        call    bfactor
        add     esp, 4
        test    eax, eax
        jns     .L16
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        push    eax
        call    rotateright
        add     esp, 4
        mov     edx, DWORD [ebp+8]
        mov     DWORD [edx+116], eax
.L16:
        push    DWORD [ebp+8]
        call    rotateleft
        add     esp, 4
        jmp     .L17
.L15:
        push    DWORD [ebp+8]
        call    bfactor
        add     esp, 4
        cmp     eax, -2
        jne     .L18
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        push    eax
        call    bfactor
        add     esp, 4
        test    eax, eax
        jle     .L19
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        push    eax
        call    rotateleft
        add     esp, 4
        mov     edx, DWORD [ebp+8]
        mov     DWORD [edx+112], eax
.L19:
        push    DWORD [ebp+8]
        call    rotateright
        add     esp, 4
        jmp     .L17
.L18:
        mov     eax, DWORD [ebp+8]
.L17:
        leave
        ret
insert:
        push    ebp
        mov     ebp, esp
        sub     esp, 24
        cmp     DWORD [ebp+8], 0
        jne     .L21
        sub     esp, 12
        push    120
        call    malloc
        add     esp, 16
        mov     DWORD [ebp-12], eax
        mov     eax, DWORD [ebp-12]
        mov     BYTE [eax], 0
        mov     eax, DWORD [ebp-12]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    strcpy
        add     esp, 16
        mov     eax, DWORD [ebp-12]
        mov     edx, DWORD [ebp+16]
        mov     DWORD [eax+104], edx
        mov     eax, DWORD [ebp-12]
        mov     BYTE [eax+108], 1
        mov     eax, DWORD [ebp-12]
        mov     DWORD [eax+112], 0
        mov     eax, DWORD [ebp-12]
        mov     DWORD [eax+116], 0
        mov     eax, DWORD [ebp-12]
        jmp     .L22
.L21:
        mov     eax, DWORD [ebp+8]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L23
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        sub     esp, 4
        push    DWORD [ebp+16]
        push    DWORD [ebp+12]
        push    eax
        call    insert
        add     esp, 16
        mov     edx, DWORD [ebp+8]
        mov     DWORD [edx+112], eax
        jmp     .L24
.L23:
        mov     eax, DWORD [ebp+8]
        sub     esp, 8
        push    eax
        push    DWORD [ebp+12]
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L25
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        sub     esp, 4
        push    DWORD [ebp+16]
        push    DWORD [ebp+12]
        push    eax
        call    insert
        add     esp, 16
        mov     edx, DWORD [ebp+8]
        mov     DWORD [edx+116], eax
        jmp     .L24
.L25:
        mov     eax, DWORD [ebp+8]
        mov     edx, DWORD [ebp+16]
        mov     DWORD [eax+104], edx
.L24:
        sub     esp, 12
        push    DWORD [ebp+8]
        call    balance
        add     esp, 16
.L22:
        leave
        ret
findmin:
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        test    eax, eax
        je      .L27
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        sub     esp, 12
        push    eax
        call    findmin
        add     esp, 16
        jmp     .L29
.L27:
        mov     eax, DWORD [ebp+8]
.L29:
        leave
        ret
removemin:
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        test    eax, eax
        jne     .L31
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        jmp     .L32
.L31:
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        sub     esp, 12
        push    eax
        call    removemin
        add     esp, 16
        mov     edx, DWORD [ebp+8]
        mov     DWORD [edx+112], eax
        sub     esp, 12
        push    DWORD [ebp+8]
        call    balance
        add     esp, 16
.L32:
        leave
        ret
remove_node:
        push    ebp
        mov     ebp, esp
        sub     esp, 24
        cmp     DWORD [ebp+8], 0
        jne     .L34
        mov     eax, 0
        jmp     .L35
.L34:
        mov     eax, DWORD [ebp+8]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L36
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    remove_node
        add     esp, 16
        mov     edx, DWORD [ebp+8]
        mov     DWORD [edx+112], eax
        jmp     .L37
.L36:
        mov     eax, DWORD [ebp+8]
        sub     esp, 8
        push    eax
        push    DWORD [ebp+12]
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L38
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    remove_node
        add     esp, 16
        mov     edx, DWORD [ebp+8]
        mov     DWORD [edx+116], eax
        jmp     .L37
.L38:
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        mov     DWORD [ebp-12], eax
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        mov     DWORD [ebp-16], eax
        sub     esp, 12
        push    DWORD [ebp+8]
        call    free
        add     esp, 16
        cmp     DWORD [ebp-16], 0
        jne     .L39
        mov     eax, DWORD [ebp-12]
        jmp     .L35
.L39:
        sub     esp, 12
        push    DWORD [ebp-16]
        call    findmin
        add     esp, 16
        mov     DWORD [ebp-20], eax
        sub     esp, 12
        push    DWORD [ebp-16]
        call    removemin
        add     esp, 16
        mov     edx, DWORD [ebp-20]
        mov     DWORD [edx+116], eax
        mov     eax, DWORD [ebp-20]
        mov     edx, DWORD [ebp-12]
        mov     DWORD [eax+112], edx
        sub     esp, 12
        push    DWORD [ebp-20]
        call    balance
        add     esp, 16
        jmp     .L35
.L37:
        sub     esp, 12
        push    DWORD [ebp+8]
        call    balance
        add     esp, 16
.L35:
        leave
        ret
find:
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        cmp     DWORD [ebp+8], 0
        je      .L41
        mov     eax, DWORD [ebp+8]
        sub     esp, 8
        push    eax
        push    DWORD [ebp+12]
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L42
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+116]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    find
        add     esp, 16
        jmp     .L43
.L42:
        mov     eax, DWORD [ebp+8]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L44
        mov     eax, DWORD [ebp+8]
        mov     eax, DWORD [eax+112]
        sub     esp, 8
        push    DWORD [ebp+12]
        push    eax
        call    find
        add     esp, 16
        jmp     .L43
.L44:
        mov     eax, DWORD [ebp+8]
        jmp     .L43
.L41:
        mov     eax, 0
.L43:
        leave
        ret

my_main:
        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ecx
        sub     esp, 148
        sub     esp, 8
        push    LC0
        push    LC1
        call    fopen
        add     esp, 16
        mov     DWORD [ebp-24], eax
        sub     esp, 8
        push    LC2
        push    LC3
        call    fopen
        add     esp, 16
        mov     DWORD [ebp-28], eax
        mov     DWORD [ebp-12], 0
        sub     esp, 4
        lea     eax, [ebp-36]
        push    eax
        push    LC4
        push    DWORD [ebp-24]
        call    fscanf
        add     esp, 16
        mov     DWORD [ebp-16], 0
        jmp     .L46
.L47:
        lea     eax, [ebp-148]
        push    eax
        lea     eax, [ebp-141]
        push    eax
        push    LC5
        push    DWORD [ebp-24]
        call    fscanf
        add     esp, 16
        mov     eax, DWORD [ebp-148]
        sub     esp, 4
        push    eax
        lea     eax, [ebp-141]
        push    eax
        push    DWORD [ebp-12]
        call    insert
        add     esp, 16
        mov     DWORD [ebp-12], eax
        add     DWORD [ebp-16], 1
.L46:
        mov     eax, DWORD [ebp-36]
        cmp     DWORD [ebp-16], eax
        jl      .L47
        sub     esp, 4
        lea     eax, [ebp-40]
        push    eax
        push    LC4
        push    DWORD [ebp-24]
        call    fscanf
        add     esp, 16
        mov     DWORD [ebp-20], 0
        jmp     .L48
.L51:
        sub     esp, 4
        lea     eax, [ebp-141]
        push    eax
        push    LC6
        push    DWORD [ebp-24]
        call    fscanf
        add     esp, 16
        sub     esp, 8
        lea     eax, [ebp-141]
        push    eax
        push    DWORD [ebp-12]
        call    find
        add     esp, 16
        mov     DWORD [ebp-32], eax
        cmp     DWORD [ebp-32], 0
        je      .L49
        mov     eax, DWORD [ebp-32]
        mov     eax, DWORD [eax+104]
        sub     esp, 4
        push    eax
        push    LC7
        push    DWORD [ebp-28]
        call    fprintf
        add     esp, 16
        jmp     .L50
.L49:
        push    DWORD [ebp-28]
        push    3
        push    1
        push    LC8
        call    fwrite
        add     esp, 16
.L50:
        add     DWORD [ebp-20], 1
.L48:
        mov     eax, DWORD [ebp-40]
        cmp     DWORD [ebp-20], eax
        jl      .L51
        sub     esp, 12
        push    DWORD [ebp-24]
        call    fclose
        add     esp, 16
        sub     esp, 12
        push    DWORD [ebp-28]
        call    fclose
        add     esp, 16
        mov     eax, 0
        mov     ecx, DWORD [ebp-4]
        leave
        lea     esp, [ecx-4]
        ret