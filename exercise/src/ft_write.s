section .text
    global ft_write
    extern __errno_location

ft_write:
    mov rax, 1  ; syscall number for write = 1
    syscall
    test rax, rax
    js .error
    ret         ; return to caller (bytes written, or -errno on error)

.error:
    neg rax
    push rax
    call __errno_location wrt ..plt
    pop rdx
    mov [rax], edx
    mov rax, -1
    ret
