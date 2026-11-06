section .text
    global ft_calloc
    extern malloc
    extern __errno_location

ft_calloc:
    push rbx

    mov rax, rdi
    mul rsi

    jc .overflow

    mov rbx, rax
    mov rdi, rax
    call malloc wrt ..plt
    test rax, rax
    jz .malloc_fail

    mov rdi, rax
    mov rcx, rbx
    xor eax, eax
    cld
    rep stosb

    sub rdi, rbx
    mov rax, rdi
    pop rbx
    ret

.malloc_fail:
    pop rbx
    ret

.overflow:
    call __errno_location wrt ..plt
    mov dword [rax], 12
    xor eax, eax
    pop rbx
    ret
