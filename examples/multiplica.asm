; Faça um programa que multiplica dois valores dados por v1 e v2
goto main
wb 0

res  ww 0
v1   ww 30
v2   ww 500
aux2 ww 0
dec  ww 1

main:
    add x, v2
    jmz x, final
    sub x, v2       ;zera
    
    add x, v1
    add x, res
    mov x, res
    sub x, res      ;zera
    
    add x, v2
    sub x, dec
    mov x, v2
    sub x, v2
    
    goto main

final:
    halt
