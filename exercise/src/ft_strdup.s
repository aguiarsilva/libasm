section .text
    global ft_strdup

extern malloc
extern ft_strcpy
extern ft_strlen

ft_strdup:
    push rdi

    call ft_strlen

    inc rax
    mov rdi, rax

    call malloc wrt ..plt

    test rax, rax
    jz .malloc_fail

    mov rdi, rax
    mov rsi, [rsp]

    call ft_strcpy

    add rsp, 8
    ret
    
.malloc_fail:
    add rsp, 8
    ret
