section .data
    pahtname DD "/home/bruno/42/Advanced/libasm/test_file.txt"
    toWrite DD "Hello World!",0AH,9DH,"$"
section .text
global main

main:
    MOV eax,5
    MOV ebx,pathname
    MOV ecx,101o
    MOV edx,700o
    INT 80h

    MOV ebx,eax
    MOV eax,4
    MOV ecx,toWrite
    MOV edx,15
    INT 80h

    MOV eax,1
    MOV ebx,0

