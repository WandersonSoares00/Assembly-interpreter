; Faça um programa que calcula a^b e grave na word 1 da memória

goto main
wb 0

res  ww 1
a    ww 2
b    ww 10
one  ww 1

main:
    add x, b
    jmz x, final
    sub x, one
    mov x, b
    sub x, b

    add x, res
    mul x, a
    mov x, res
    sub x, res

    goto main

final:
    halt
