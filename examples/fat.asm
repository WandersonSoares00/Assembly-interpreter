goto main
wb 0

res ww 1
a   ww 20
one ww 1

main:
    add x, a        ; x += a
    jmz x, final    ; if x==0 goto final

    mul x, res      ; x *= res
    mov x, res      ; res = x
    sub x, res      ; x -= res  ; x=0

    add x, a        ; x += a
    sub x, one      ; x -= 1
    mov x, a        ; a = x
    sub x, a        ; x -= a    ; x=0

    goto main       ; loop

final:
    halt            ; encerra o programa
