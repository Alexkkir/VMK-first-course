%include "io.inc"

;CEXTERN _?_isoc99_scanf
CEXTERN scanf
CEXTERN malloc
CEXTERN free
CEXTERN printf
    

section .data:
    LC0 db `%lld %lld\n`, 0
    LC1 db '%c', 0
    LC2 db '%lld', 0
    
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
        cmp     DWORD  [ebp+8], 0
        je      .L2
        mov     eax, DWORD  [ebp+8]
        movzx   eax, BYTE  [eax+16]
        jmp     .L4
.L2:
        mov     eax, 0
.L4:
        pop     ebp
        ret
is_first_bigger_than_second:
        push    ebp
        mov     ebp, esp
        push    ebx
        sub     esp, 20
        mov     eax, DWORD  [ebp+8]
        mov     DWORD  [ebp-16], eax
        mov     eax, DWORD  [ebp+12]
        mov     DWORD  [ebp-12], eax
        mov     eax, DWORD  [ebp+16]
        mov     DWORD  [ebp-24], eax
        mov     eax, DWORD  [ebp+20]
        mov     DWORD  [ebp-20], eax
        mov     ebx, 1
        mov     eax, DWORD  [ebp-16]
        mov     edx, DWORD  [ebp-12]
        mov     ecx, DWORD  [ebp-20]
        cmp     DWORD  [ebp-24], eax
        sbb     ecx, edx
        jl      .L6
        mov     ebx, 0
.L6:
        movzx   eax, bl
        mov     ebx, DWORD  [ebp-4]
        leave
        ret
bfactor:
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        push    eax
        call    height
        add     esp, 4
        movzx   ebx, al
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        push    eax
        call    height
        add     esp, 4
        movzx   edx, al
        mov     eax, ebx
        sub     eax, edx
        mov     ebx, DWORD  [ebp-4]
        leave
        ret
fixheight:
        push    ebp
        mov     ebp, esp
        sub     esp, 16
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        push    eax
        call    height
        add     esp, 4
        mov     BYTE  [ebp-1], al
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        push    eax
        call    height
        add     esp, 4
        mov     BYTE  [ebp-2], al
        movzx   edx, BYTE  [ebp-2]
        movzx   eax, BYTE  [ebp-1]
        cmp     dl, al
        cmovnb  eax, edx
        lea     edx, [eax+1]
        mov     eax, DWORD  [ebp+8]
        mov     BYTE  [eax+16], dl
        nop
        leave
        ret
rotateright:
        push    ebp
        mov     ebp, esp
        sub     esp, 16
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        mov     DWORD  [ebp-4], eax
        mov     eax, DWORD  [ebp-4]
        mov     edx, DWORD  [eax+24]
        mov     eax, DWORD  [ebp+8]
        mov     DWORD  [eax+20], edx
        mov     eax, DWORD  [ebp-4]
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [eax+24], edx
        push    DWORD  [ebp+8]
        call    fixheight
        add     esp, 4
        push    DWORD  [ebp-4]
        call    fixheight
        add     esp, 4
        mov     eax, DWORD  [ebp-4]
        leave
        ret
rotateleft:
        push    ebp
        mov     ebp, esp
        sub     esp, 16
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        mov     DWORD  [ebp-4], eax
        mov     eax, DWORD  [ebp-4]
        mov     edx, DWORD  [eax+20]
        mov     eax, DWORD  [ebp+8]
        mov     DWORD  [eax+24], edx
        mov     eax, DWORD  [ebp-4]
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [eax+20], edx
        push    DWORD  [ebp+8]
        call    fixheight
        add     esp, 4
        push    DWORD  [ebp-4]
        call    fixheight
        add     esp, 4
        mov     eax, DWORD  [ebp-4]
        leave
        ret
balance:
        push    ebp
        mov     ebp, esp
        push    DWORD  [ebp+8]
        call    fixheight
        add     esp, 4
        push    DWORD  [ebp+8]
        call    bfactor
        add     esp, 4
        cmp     eax, 2
        jne     .L16
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        push    eax
        call    bfactor
        add     esp, 4
        test    eax, eax
        jns     .L17
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        push    eax
        call    rotateright
        add     esp, 4
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [edx+24], eax
.L17:
        push    DWORD  [ebp+8]
        call    rotateleft
        add     esp, 4
        jmp     .L18
.L16:
        push    DWORD  [ebp+8]
        call    bfactor
        add     esp, 4
        cmp     eax, -2
        jne     .L19
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        push    eax
        call    bfactor
        add     esp, 4
        test    eax, eax
        jle     .L20
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        push    eax
        call    rotateleft
        add     esp, 4
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [edx+20], eax
.L20:
        push    DWORD  [ebp+8]
        call    rotateright
        add     esp, 4
        jmp     .L18
.L19:
        mov     eax, DWORD  [ebp+8]
.L18:
        leave
        ret
insert:
        push    ebp
        mov     ebp, esp
        sub     esp, 40
        mov     eax, DWORD  [ebp+12]
        mov     DWORD  [ebp-32], eax
        mov     eax, DWORD  [ebp+16]
        mov     DWORD  [ebp-28], eax
        mov     eax, DWORD  [ebp+20]
        mov     DWORD  [ebp-40], eax
        mov     eax, DWORD  [ebp+24]
        mov     DWORD  [ebp-36], eax
        cmp     DWORD  [ebp+8], 0
        jne     .L22
        sub     esp, 12
        push    28
        call    malloc
        add     esp, 16
        mov     DWORD  [ebp-12], eax
        mov     ecx, DWORD  [ebp-12]
        mov     eax, DWORD  [ebp-32]
        mov     edx, DWORD  [ebp-28]
        mov     DWORD  [ecx], eax
        mov     DWORD  [ecx+4], edx
        mov     ecx, DWORD  [ebp-12]
        mov     eax, DWORD  [ebp-40]
        mov     edx, DWORD  [ebp-36]
        mov     DWORD  [ecx+8], eax
        mov     DWORD  [ecx+12], edx
        mov     eax, DWORD  [ebp-12]
        mov     BYTE  [eax+16], 1
        mov     eax, DWORD  [ebp-12]
        mov     DWORD  [eax+20], 0
        mov     eax, DWORD  [ebp-12]
        mov     DWORD  [eax+24], 0
        mov     eax, DWORD  [ebp-12]
        jmp     .L23
.L22:
        mov     eax, DWORD  [ebp+8]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        push    DWORD  [ebp-28]
        push    DWORD  [ebp-32]
        push    edx
        push    eax
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L24
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        sub     esp, 12
        push    DWORD  [ebp-36]
        push    DWORD  [ebp-40]
        push    DWORD  [ebp-28]
        push    DWORD  [ebp-32]
        push    eax
        call    insert
        add     esp, 32
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [edx+20], eax
        jmp     .L25
.L24:
        mov     eax, DWORD  [ebp+8]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        push    edx
        push    eax
        push    DWORD  [ebp-28]
        push    DWORD  [ebp-32]
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L26
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        sub     esp, 12
        push    DWORD  [ebp-36]
        push    DWORD  [ebp-40]
        push    DWORD  [ebp-28]
        push    DWORD  [ebp-32]
        push    eax
        call    insert
        add     esp, 32
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [edx+24], eax
        jmp     .L25
.L26:
        mov     ecx, DWORD  [ebp+8]
        mov     eax, DWORD  [ebp-40]
        mov     edx, DWORD  [ebp-36]
        mov     DWORD  [ecx+8], eax
        mov     DWORD  [ecx+12], edx
.L25:
        sub     esp, 12
        push    DWORD  [ebp+8]
        call    balance
        add     esp, 16
.L23:
        leave
        ret
findmin:
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        test    eax, eax
        je      .L28
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        sub     esp, 12
        push    eax
        call    findmin
        add     esp, 16
        jmp     .L30
.L28:
        mov     eax, DWORD  [ebp+8]
.L30:
        leave
        ret
removemin:
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        test    eax, eax
        jne     .L32
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        jmp     .L33
.L32:
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        sub     esp, 12
        push    eax
        call    removemin
        add     esp, 16
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [edx+20], eax
        sub     esp, 12
        push    DWORD  [ebp+8]
        call    balance
        add     esp, 16
.L33:
        leave
        ret
remove_node:
        push    ebp
        mov     ebp, esp
        sub     esp, 40
        mov     eax, DWORD  [ebp+12]
        mov     DWORD  [ebp-32], eax
        mov     eax, DWORD  [ebp+16]
        mov     DWORD  [ebp-28], eax
        cmp     DWORD  [ebp+8], 0
        jne     .L35
        mov     eax, 0
        jmp     .L36
.L35:
        mov     eax, DWORD  [ebp+8]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        mov     ecx, DWORD  [ebp-28]
        cmp     DWORD  [ebp-32], eax
        sbb     ecx, edx
        jge     .L37
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        sub     esp, 4
        push    DWORD  [ebp-28]
        push    DWORD  [ebp-32]
        push    eax
        call    remove_node
        add     esp, 16
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [edx+20], eax
        jmp     .L38
.L37:
        mov     eax, DWORD  [ebp+8]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        cmp     eax, DWORD  [ebp-32]
        mov     eax, edx
        sbb     eax, DWORD  [ebp-28]
        jge     .L39
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        sub     esp, 4
        push    DWORD  [ebp-28]
        push    DWORD  [ebp-32]
        push    eax
        call    remove_node
        add     esp, 16
        mov     edx, DWORD  [ebp+8]
        mov     DWORD  [edx+24], eax
        jmp     .L38
.L39:
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        mov     DWORD  [ebp-12], eax
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        mov     DWORD  [ebp-16], eax
        sub     esp, 12
        push    DWORD  [ebp+8]
        call    free
        add     esp, 16
        cmp     DWORD  [ebp-16], 0
        jne     .L40
        mov     eax, DWORD  [ebp-12]
        jmp     .L36
.L40:
        sub     esp, 12
        push    DWORD  [ebp-16]
        call    findmin
        add     esp, 16
        mov     DWORD  [ebp-20], eax
        sub     esp, 12
        push    DWORD  [ebp-16]
        call    removemin
        add     esp, 16
        mov     edx, DWORD  [ebp-20]
        mov     DWORD  [edx+24], eax
        mov     eax, DWORD  [ebp-20]
        mov     edx, DWORD  [ebp-12]
        mov     DWORD  [eax+20], edx
        sub     esp, 12
        push    DWORD  [ebp-20]
        call    balance
        add     esp, 16
        jmp     .L36
.L38:
        sub     esp, 12
        push    DWORD  [ebp+8]
        call    balance
        add     esp, 16
.L36:
        leave
        ret
find:
        push    ebp
        mov     ebp, esp
        sub     esp, 24
        mov     eax, DWORD  [ebp+12]
        mov     DWORD  [ebp-16], eax
        mov     eax, DWORD  [ebp+16]
        mov     DWORD  [ebp-12], eax
        cmp     DWORD  [ebp+8], 0
        je      .L42
        mov     eax, DWORD  [ebp+8]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        push    edx
        push    eax
        push    DWORD  [ebp-12]
        push    DWORD  [ebp-16]
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L43
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        sub     esp, 4
        push    DWORD  [ebp-12]
        push    DWORD  [ebp-16]
        push    eax
        call    find
        add     esp, 16
        jmp     .L44
.L43:
        mov     eax, DWORD  [ebp+8]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        push    DWORD  [ebp-12]
        push    DWORD  [ebp-16]
        push    edx
        push    eax
        call    is_first_bigger_than_second
        add     esp, 16
        test    eax, eax
        je      .L45
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        sub     esp, 4
        push    DWORD  [ebp-12]
        push    DWORD  [ebp-16]
        push    eax
        call    find
        add     esp, 16
        jmp     .L44
.L45:
        mov     eax, DWORD  [ebp+8]
        jmp     .L44
.L42:
        mov     eax, 0
.L44:
        leave
        ret

some_print:
        push    ebp
        mov     ebp, esp
        push    ebx
        sub     esp, 4
        cmp     DWORD  [ebp+8], 0
        je      .L48
        mov     eax, DWORD  [ebp+8]
        mov     ecx, DWORD  [eax+8]
        mov     ebx, DWORD  [eax+12]
        mov     eax, DWORD  [ebp+8]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        sub     esp, 12
        push    ebx
        push    ecx
        push    edx
        push    eax
        push    LC0
        call    printf
        add     esp, 32
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+20]
        sub     esp, 12
        push    eax
        call    some_print
        add     esp, 16
        mov     eax, DWORD  [ebp+8]
        mov     eax, DWORD  [eax+24]
        sub     esp, 12
        push    eax
        call    some_print
        add     esp, 16
.L48:
        nop
        mov     ebx, DWORD  [ebp-4]
        leave
        ret

my_main:
        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD  [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ebx
        push    ecx
        sub     esp, 32
        mov     DWORD  [ebp-12], 0
        mov     DWORD  [ebp-16], 1
        jmp     .L50
.L57:
        sub     esp, 8
        lea     eax, [ebp-21]
        push    eax
        push    LC1
        call    scanf
        add     esp, 16
        movzx   eax, BYTE  [ebp-21]
        movsx   eax, al
        cmp     eax, 83
        je      .L51
        cmp     eax, 83
        jg      .L59
        cmp     eax, 70
        je      .L53
        cmp     eax, 70
        jg      .L59
        cmp     eax, 65
        je      .L54
        cmp     eax, 68
        je      .L55
        jmp     .L52
.L54:
        sub     esp, 8
        lea     eax, [ebp-32]
        push    eax
        push    LC2
        call    scanf
        add     esp, 16
        sub     esp, 8
        lea     eax, [ebp-40]
        push    eax
        push    LC2
        call    scanf
        add     esp, 16
        mov     ecx, DWORD  [ebp-40]
        mov     ebx, DWORD  [ebp-36]
        mov     eax, DWORD  [ebp-32]
        mov     edx, DWORD  [ebp-28]
        sub     esp, 12
        push    ebx
        push    ecx
        push    edx
        push    eax
        push    DWORD  [ebp-12]
        call    insert
        add     esp, 32
        mov     DWORD  [ebp-12], eax
        jmp     .L50
.L55:
        sub     esp, 8
        lea     eax, [ebp-32]
        push    eax
        push    LC2
        call    scanf
        add     esp, 16
        mov     eax, DWORD  [ebp-32]
        mov     edx, DWORD  [ebp-28]
        sub     esp, 4
        push    edx
        push    eax
        push    DWORD  [ebp-12]
        call    remove_node
        add     esp, 16
        mov     DWORD  [ebp-12], eax
        jmp     .L50
.L51:
        sub     esp, 8
        lea     eax, [ebp-32]
        push    eax
        push    LC2
        call    scanf
        add     esp, 16
        mov     eax, DWORD  [ebp-32]
        mov     edx, DWORD  [ebp-28]
        sub     esp, 4
        push    edx
        push    eax
        push    DWORD  [ebp-12]
        call    find
        add     esp, 16
        mov     DWORD  [ebp-20], eax
        cmp     DWORD  [ebp-20], 0
        je      .L50
        mov     eax, DWORD  [ebp-20]
        mov     ecx, DWORD  [eax+8]
        mov     ebx, DWORD  [eax+12]
        mov     eax, DWORD  [ebp-20]
        mov     edx, DWORD  [eax+4]
        mov     eax, DWORD  [eax]
        sub     esp, 12
        push    ebx
        push    ecx
        push    edx
        push    eax
        push    LC0
        call    printf
        add     esp, 32
        jmp     .L50
.L53:
        mov     DWORD  [ebp-16], 0
        jmp     .L50
.L52:
.L59:
        nop
.L50:
        cmp     DWORD  [ebp-16], 0
        jne     .L57
        mov     eax, 0
        lea     esp, [ebp-8]
        pop     ecx
        pop     ebx
        pop     ebp
        lea     esp, [ecx-4]
        ret