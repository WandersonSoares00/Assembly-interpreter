
goto main
wb 0

res  ww 0
val1 ww 30
val2 ww 51

main:
    add x, val1
    jmz x, final
    mul x, val2
    mov x, res

final:
    halt
