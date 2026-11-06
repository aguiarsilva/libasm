section .text
    global ft_strcmp

ft_strcmp:

.loop:
    movzx eax, byte [rdi]
    movzx ecx, byte [rsi]
    cmp al, cl
    jne .done
    test al, al
    jz .done
    inc rdi
    inc rsi
    jmp .loop

.done:
    sub eax, ecx
    ret
