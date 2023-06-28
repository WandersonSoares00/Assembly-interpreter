goto main

wb 0

res  ww 0
var1 ww 80     ; men[2] = 80
var2 ww 150    ; men[3] = 150

main:
    add x, var1    ; wb (1, add), wb (2, b)
    sub x, var2    ; wb (3, sub), wb (4, a)
    mov x, res     ; wb (5, mov), wb (6, b)
    goto final

final:
    halt           ; wb (7, halt)
