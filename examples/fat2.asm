goto main
wb 0

res ww 0
a   ww 15
one ww 1

main:
    ldr x, one        ; x = a
    ldr y, a
    
    loop:
        jmz y, final    ; if x==0 goto final

        mul x, y        ; x *= y
        sub y, one

        goto loop

final:
    mov x, res
    halt            ; encerra o programa
