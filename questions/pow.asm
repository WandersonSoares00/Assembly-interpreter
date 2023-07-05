; Programa que calcula a^b e grava o resultado na word 1 da memória

goto main
wb 0

res  ww 0
a    ww 2
b    ww 10
one  ww 1

main:
    ldr x, one
    ldr y, b

    loop:
        jmz y, final
        mul x, a
        sub y, one
        goto loop

final:
    mov x, res
    halt
