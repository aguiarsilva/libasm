section .data
    pathname DD "/home/bruno/42/Advanced/libasm/data.s"
section .bss
    buffer: resb 1024
section .text
global main

main:
    MOV eax,5
    MOV ebx,pahtname
    MOV ecx,0
    INT 80h

    MOV ebx,eax
    MOV eax,3
    MOV ecx,buffer
    MOV edx,1024
    INT 80h

    MOV eax,1
    MOV ebx,0
    INT 80h
