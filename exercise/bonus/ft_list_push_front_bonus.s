section .text
    global ft_list_push_front

extern malloc

ft_list_push_front:
    test rdi, rdi
    jz .done

    push rbx
    push r12
    sub rsp, 8
    mov rbx, rdi
    mov r12, rsi
    mov rdi, 16
    
    call malloc wrt ..plt
    add rsp, 8
    test rax, rax
    jz .done

    mov [rax], r12
    mov rdx, [rbx]
    mov [rax + 8], rdx
    mov [rbx], rax
    
    pop r12
    pop rbx
    ret

.done:
    pop r12
    pop rbx
    ret

