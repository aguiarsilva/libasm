section .text
    global ft_strlen

ft_strlen:
    xor rax, rax    ; xor is a better way to zero a register

.loop:
    cmp byte [rdi], 0   ; checks if the current byte is '\0'
    je .done            ; if is \0 then loop is done
    inc rdi             ; move to next char
    inc rax             ; count it
    jmp .loop

.done:
    ret

