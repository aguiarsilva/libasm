section .data
    msg db 'Hello, World!', 0xA ; String with newline (0xA)
    len equ $ - msg             ; Length of the String

section .text
    global _start

_start:
    ; Write syscall: 1 (stdout), pointer to msg, length
    mov eax, 4      ; sys_write
    mov ebx, 1      ; stdout
    mov ecx, msg    ; pointer to String
    mov edx, len    ; length
    int 0x80        ; invoke syscall

    ; Exit syscall: 0 (success)
    mov eax, 1      ; sys_exit
    mov ebx, 0      ; exit code
    int 0x80        ; invoke syscall
