; 2. Calcula a divisão inteira de a por b e armazena na word 1 da memória e o resto da divisão na word 2

goto main
wb 0

int    ww 0        ; divisao inteira
rest   ww 0        ; resto da divisão
a      ww 562
b      ww 4
one    ww 1

main:
    ldr x, a      
    div x, b      
    mov x, int    

    ldr y, b      
    mul y, int    
    ldr x, a      
    sub x, y      
    mov x, rest   

    halt
