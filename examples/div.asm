
goto main
wb 0

res  ww 0
val1 ww 50
val2 ww 200

main:
    add x, val1
    jmz x, final
    div x, val2
    mov x, res

final:
    halt
