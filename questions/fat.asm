; programa que calcula o fatorial da variável "a" e armazena o resultado na word 1 da memória
goto main
wb 0

res ww 0
a   ww 15
one ww 1

main:
    ldr x, one          ; x = one
    ldr y, a            ; y = a

    loop:
        jmz y, final    ; if x==0 goto final

        mul x, y        ; x = x * y
        sub y, one      ; y = y - 1

        goto loop

final:
    mov x, res          ; memory[res] = x
    halt
