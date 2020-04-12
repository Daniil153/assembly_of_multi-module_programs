
section .text
global f1
global f2
global f3
global csqrt
csqrt:
    push ebp
    mov ebp, esp
    sub esp, 24
    
    finit
    fld qword[ebp + 8]
    fsqrt

    add esp, 24
    pop ebp
    ret
f1:
    push ebp
    mov ebp, esp
    sub esp, 24
    
    finit
    fld qword[ebp+8]
    fldl2e
    fmulp   st1, st0
    fld1
    fld     st1
    fprem
    f2xm1
    faddp   st1, st0
    fscale
    fstp    st1
    fld1
    fld1
    faddp
    faddp
    
    add esp, 24
    pop ebp
    ret
    
f2:
    push ebp
    mov ebp, esp
    sub esp, 24
    
    finit
    fld1
    fchs
    fld qword[ebp+8]
    fdivp
    
    add esp, 24
    pop ebp
    ret
    
f3:
    push ebp
    mov ebp, esp
    sub esp, 24
    
    finit
    fld1
    fld1
    faddp
    fchs
    fld qword[ebp+8]
    fld1
    faddp
    fmulp
    fld1
    fld1
    fld1
    faddp
    faddp
    fdivp
    
    add esp, 24
    pop ebp
    ret
