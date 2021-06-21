section .text
global f1
global f2
global f3

section .data
    _m2 dq -2.0
    _14 dq 14.0
    _1 dq 1.0
    _2 dq 2.0
    _6 dq 6.0
    
f1:
    push ebp
    mov ebp, esp
    
    fldln2 
    fld qword [ebp + 8]
    fyl2x
    
    mov esp, ebp
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    
    fld qword [epb + 8]
    fld qword [_m2]
    fmulp
    fld qword [_14]
    faddp   
    
    mov esp, ebp
    pop ebp
    ret
    
f3:
    push ebp
    mov ebp, esp
    
    fld qword [_1]
    fld qword [_2]
    fld qword [ebp + 8]
    fsubp
    fdivp
    fld qword [_6]
    faddp
    
    mov esp, ebp
    pop ebp
    ret
    
f1_d:
    push ebp
    mov ebp, esp
    
    fld qword [_1]
    fld qword [ebp + 8]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
    
f2_d:
    push ebp
    mov ebp, esp
    
    fld qword [_2]
    
    mov esp, ebp
    pop ebp
    ret
    
f3_d:
    push ebp
    mov ebp, esp
    
    fld qword [_1]
    fld qword [ebp + 8]
    fld qword [_m2]
    faddp
    fld qword [ebp + 8]
    fld qword [_m2]
    faddp
    fmulp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
    
    
    