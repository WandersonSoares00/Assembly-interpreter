add x, b    ; wb (1, add), wb (2, b)
sub x, a    ; wb (3, sub), wb (4, a)
mov x, b    ; wb (5, mov), wb (6, b)
halt        ; wb (7, halt)

a ww 80     ; men[2] = 80
b ww 150    ; men[3] = 150
