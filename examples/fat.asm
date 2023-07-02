goto main
wb 0

res ww 1
a   ww 15
one ww 1

main:
    ldr x, a        ; x = a
    jmz x, final    ; if x==0 goto final

    mul x, res      ; x *= res
    mov x, res      ; res = x

    ldr x, a        ; x = a
    sub x, one      ; x -= 1
    mov x, a        ; a = x

    goto main       ; loop

final:
    halt            ; encerra o programa
