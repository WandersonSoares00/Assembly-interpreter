
/*
    *Implementação de um computador de propósito geral, segue o conjunto de instruções:
    * 1) main: PC <- PC + 1; MBR <- read_byte(PC); GOTO MBR
    * 2) X = X + mem[address]
    * 3) mem[address] = X
    * 4) goto address
    * 5) if X = 0 then goto address (próximo)
    * 6) X = X - mem[address]
    * 7) halt
*/
// Operando: valor para que a instrução precisa para executar
//      x == y  ?

unsigned long int* get_firmware (){
        unsigned long int *firmware = new unsigned long int[512];

        /*      Instrução 1     */
        // incrementa pc, carrega o endereço da instrução no mbr e vai executar a instrução(goto mbr)
        firmware[0] =   0b000000000'100'00110101'001000'001'001;

        /*      Instrução 2  ->  X = X + mem[address]   */
        //firmware[1] =   0b000000000'000'00000000'000000'000'000;
        // 2: PC <- PC + 1; MBR <- read_byte(PC); GOTO 3
        // 3: MAR <- MBR; read_word; GOTO 4
        // 4: H <- MDR; GOTO 5
        // 5: X <- H + X; GOTO 0

        firmware[2] =   0b000000011'000'00110101'001000'001'001;
        firmware[3] =   0b000000100'000'00010100'100000'010'010;
        firmware[4] =   0b000000101'000'00010100'000001'000'000;
        firmware[5] =   0b000000000'000'00111100'000100'000'011;

        /*      Instrução 3    ->  mem[address] = X  */
        //  6: PC <- PC + 1; fetch; GOTO 7
        //  7: MAR <- MBR; GOTO 8
        //  8: MDR <- X; write; GOTO 0
        firmware[6]  =  0b000000111'000'00110101'001000'001'001;
        firmware[7]  =  0b000001000'000'00010100'100000'000'010;
        firmware[8]  =  0b000000000'000'00010100'010000'100'011;

        /*      Instrução 4    ->  goto address    */
        //  9: PC <- PC + 1; fetch; GOTO 10
        //  10: PC <- MBR; fetch; GOTO MBR
        firmware[9]  =  0b000001010'000'00110101'001000'001'001;
        firmware[10] =  0b000000000'100'00010100'001000'001'010;

        /*      Instrução 5   ->  if X = 0 then goto address */
        // 11: X <- X; IF ALU = 0 GOTO 268(100001100, bit + sig do jam) (256 à frente) ELSE GOTO 12(000001100)
        // 12: 12: PC <- PC + 1; GOTO 0
        // 268: GOTO 9
        firmware[11]  =  0b000001100'001'00010100'000100'000'011;
        firmware[12]  =  0b000000000'000'00110101'001000'000'001;
        firmware[268] =  0b000001001'000'00000000'000000'000'000;

        /*      Instrução 6  ->  X = X - mem[address]    */
        //  13: PC <- PC + 1; fetch; goto 14
        //  14: MAR <- MBR; read; goto 15
        //  15: H <- MDR; goto 16
        //  16: X <- X - H; goto 0
        firmware[13]  =  0b000001110'000'00110101'001000'001'001;
        firmware[14]  =  0b000001111'000'00010100'100000'010'010;
        firmware[15]  =  0b000010000'000'00010100'000001'000'000;
        firmware[16]  =  0b000000000'000'00111111'000100'000'011;


        /*    Instrução 7   -> halt      */
        firmware[255] = 0;    // 7

        return firmware;
}




