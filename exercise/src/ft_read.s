section .text
    global ft_read
    extern __errno_location

ft_read:
    mov rax, 0
    syscall

    test rax, rax
    js .error

    ret

.error:
    neg rax
    push rax
    call __errno_location wrt ..plt
    pop rdx
    mov [rax], edx
    mov rax, -1
    ret

