
goto main
wb 0

res  ww 0
val1 ww 30
val2 ww 51

main:
    add y, val1
    jmz y, final
    mul y, val2
    mov y, res

final:
    halt
