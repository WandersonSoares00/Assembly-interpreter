#ifndef FIRMWARE_HPP
#define FIRMWARE_HPP

/*
    *Implementação de um computador de propósito geral, segue o conjunto de instruções:
    * 1) main: PC <- PC + 1; MBR <- read_byte(PC); GOTO MBR
    * 2) X = X + mem[address]
    * 3) mem[address] = X
    * 4) goto address
    * 5) if X = 0 then goto address (próximo)
    * 6) X = X - mem[address]
    * 7) X = X * men[address]
    * 8) X = X / men[address]
    * 9) X = mem[address]
    * 10) halt
*/

// Operando: valor para que a instrução precisa para executar
//      x == y  ?

// 9 (next) + 3 (jam) + 8 (alu) + 6 (c) + 3 (men) + 3 (b) + 3 (a)
/*
fetch: ++pc, MBR <- read_byte(PC), mar <- mbr : 2, 6, 
*/
long int* get_firmware (){
        long int *firmware = new long int[512];

        /*      Instrução 1     */
        // incrementa pc, carrega o endereço da instrução no mbr e vai executar a instrução(goto mbr)
        firmware[0] =   0b000000000'100'00000000'000000'000'001'000'000;

        /*      Instrução 2  ->  X = X + mem[address]   */
        //firmware[1] =   0b000000000'000'00000000'000000'000'000;
        // 2: PC <- PC + 1; MBR <- read_byte(PC); GOTO 3
        // 3: MAR <- MBR; read_word; GOTO 4
        // 4: H <- MDR; GOTO 5
        // 5: X <- H + X; GOTO 0
        firmware[2] =   0b000000000'000'00111100'000100'000'011'000'011;

        /*      Instrução 3    ->  mem[address] = X  */
        //  6: PC <- PC + 1; fetch; GOTO 7
        //  7: MAR <- MBR; GOTO 8
        //  8: MDR <- X; write; GOTO 0
        
        firmware[6]  =  0b000000000'000'00010100'010000'100'011'000'011;

        /*      Instrução 4    ->  goto address    */
        //  9: PC <- PC + 1; fetch; GOTO 10
        //  10: PC <- MBR; fetch; GOTO MBR
        firmware[9]  =  0b000000000'100'00010100'001000'001'001'000'010;

        /*      Instrução 5   ->  if X = 0 then goto address */
        // 11: X <- X; IF ALU = 0 GOTO 268(100001100, bit + sig do jam) (256 à frente) ELSE GOTO 12(000001100)
        // 12: 12: PC <- PC + 1; GOTO 0
        // 268: GOTO 9
        firmware[11]  =  0b000001100'001'00010100'000100'000'000'000'011;
        firmware[12]  =  0b000000000'000'00110101'001000'000'000'000'001;
        firmware[268] =  0b000001001'000'00000000'000000'000'000'000'000;

        /*      Instrução 6  ->  X = X - mem[address]    */
        //  13: PC <- PC + 1; fetch; goto 14
        //  14: MAR <- MBR; read; goto 15
        //  15: H <- MDR; goto 16
        //  16: X <- X - H; goto 0
        firmware[13]  =  0b000000000'000'00111111'000100'000'011'000'011;

        /*      Instrução 7  ->  X = X * mem[address]    */
        //  17: PC <- PC + 1; fetch; goto 18
        //  18: MAR <- MBR; read; goto 19
        //  19: H <- MDR; goto 20
        //  20: X <- X * H; goto 0
        firmware[17]  =  0b000000000'000'00001100'000100'000'011'000'011;

        /*      Instrução 8  ->  X = X / mem[address]    */
        //  17: PC <- PC + 1; fetch; goto 21
        //  18: MAR <- MBR; read; goto 22
        //  19: H <- MDR; goto 23
        //  20: X <- X / H; goto 0
        firmware[21]  =  0b000000000'000'00011100'000100'000'011'000'011;

        /*      Instrução 9  ->  X = mem[address]    */
        //  6: PC <- PC + 1; fetch; GOTO 7
        //  7: MAR <- MBR; read_word; GOTO 4
        //  8: X <- MDR; GOTO 0
        
        firmware[25]  =  0b000000000'000'00010100'000100'100'011'000'000;

        /*    Instrução 10   -> halt      */
        firmware[255] = 0;    // 7

        return firmware;
}


#endif

