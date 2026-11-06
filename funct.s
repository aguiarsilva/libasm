section .data

section .text
global main

addTwo:
    PUSH ebp
    MOV ebp, esp
    MOV eax,[ebp+8]
    MOV ebx,[ebp+12]
    ADD eax,ebx
    POP ebp
    RET

main:
    MOV eax,4
    MOV ebx,1
    CALL addTwo
    MOV ebx,eax
    MOV eax,1

