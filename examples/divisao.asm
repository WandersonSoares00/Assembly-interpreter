; 2. Um programa que calcula a divisão inteira, retornando como resultado o valor da divisão e o resto
goto main
wb 0

i   ww 0        ; divisao inteira
r   ww 0        ; resto da divisão
a   ww 4
b   ww 562
one ww 1

main:
    add x, b    ; x+=b
    div x, a    ; x = a/x
    mov x, i    ; i=x   ; divisao inteira
    
    sub x, i    ; x=0
    add x, b    ; x=b

    mul x, i    ; x *= i
    mov x, b    ; b=x
    sub x, b    ; x=0
    add x, a    ; x+=a
    sub x, b    ; x-=b

    mov x, r    ; r=x

    halt        ; encerra o programa