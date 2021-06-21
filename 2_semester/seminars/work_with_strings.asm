%include "io.inc"

section .data
str1 db 'Hello, world!',0
len equ ($-str1)
str2 times len db '#'

section .text
global CMAIN

CMAIN:
    mov ebp, esp; for correct debugging
    
    lea eax, [str2 + len - 1]
    mov [eax], dword 0
    
    PRINT_STRING str1
    NEWLINE
    
    
    NEWLINE
    PRINT_STRING str2

    
    lea esi, [str1] ; адрес источника
    lea edi, [str2] ; адрес приемника
    mov ecx, len ; размер строки
    cld ; установка DF=0
    
    START: ; посимвольная
        movsb ; пересылка
        loop START ; данных
    
    NEWLINE
    NEWLINE
    PRINT_STRING str2
    NEWLINE

mov eax, 0
ret
