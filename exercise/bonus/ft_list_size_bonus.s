section .text
    global ft_list_size

ft_list_size:
    xor eax, eax

.loop:
    test rdi, rdi
    jz .done
    inc eax
    mov rdi, [rdi + 8]
    jmp .loop

.done:
    ret
