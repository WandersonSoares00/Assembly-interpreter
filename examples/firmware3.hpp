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
    * 10) Y = Y - mem[address]
    * 11) Y = Y * men[address]
    * 12) Y = Y / men[address]
    * 13) Y = mem[address]
    * 14) X = X - Y
    * 15) X = X + Y
    * 16) X = X * Y
    * 17) X = X / Y
    * 18) halt
*/

long int* get_firmware (){
        long int *firmware = new long int[512];

        /*      Instrução 1     */
        firmware[0] =   0b000000000'100'00000000'000000'000'001'000'000;


        /*      Instrução 2  ->  X = X + mem[address]   */
        firmware[2] =   0b000000000'100'00111100'000100'000'111'000'011;
        /*      Instrução 3    ->  mem[address] = X  */
        firmware[3]  =  0b000000000'100'00010100'010000'100'111'000'011;
        /*      Instrução 5   ->  if X = 0 then goto address */
        firmware[4]  =  0b000000101'001'00010100'000100'000'000'000'011;
        firmware[5]  =  0b000000000'100'00000000'000000'000'101'000'000;
        firmware[261] = 0b001100100'000'00000000'000000'000'000'000'000;
        /*      Instrução 6  ->  X = X - mem[address]    */
        firmware[6]  =  0b000000000'100'00111111'000100'000'111'000'011;
        /*      Instrução 7  ->  X = X * mem[address]    */
        firmware[7]  =  0b000000000'100'00001100'000100'000'111'000'011;
        /*      Instrução 8  ->  X = X / mem[address]    */
        firmware[8]  =  0b000000000'100'00011100'000100'000'111'000'011;
        /*      Instrução 9  ->  X = mem[address]    */
        firmware[9]  =  0b000000000'100'00010100'000100'100'111'000'000;


        /*      Instrução 2  ->  Y = Y + mem[address]   */
        firmware[18] =   0b000000000'100'00111100'000010'000'111'000'100;
        /*      Instrução 3    ->  mem[address] = Y  */
        firmware[19]  =  0b000000000'100'00010100'010000'100'111'000'100;
        /*      Instrução 5   ->  if Y = 0 then goto address */
        firmware[20]  =  0b000010101'001'00010100'000010'000'000'000'100;
        firmware[21]  =  0b000000000'100'00000000'000000'000'000'101'000;
        firmware[277] =  0b001100100'000'00000000'000000'000'000'000'000;
        /*      Instrução 6  ->  Y = Y - mem[address]    */
        firmware[22]  =  0b000000000'100'00111111'000010'000'111'000'100;
        /*      Instrução 7  ->  Y = Y * mem[address]    */
        firmware[23]  =  0b000000000'100'00001100'000010'000'111'000'100;
        /*      Instrução 8  ->  Y = Y / mem[address]    */
        firmware[24]  =  0b000000000'100'00011100'000010'000'111'000'100;
        /*      Instrução 9  ->  Y = mem[address]    */
        firmware[25]  =  0b000000000'100'00010100'000010'100'111'000'000;


        /*      Instrução 2  ->  X = X + Y   */
        firmware[34] =   0b000000000'100'00111100'000100'000'001'011'100;
        /*      Instrução 6  ->  X = X - Y    */
        firmware[35]  =  0b000000000'100'00111111'000100'000'001'011'100;
        /*      Instrução 7  ->  X = X * Y    */
        firmware[36]  =  0b000000000'100'00001100'000100'000'001'011'100;
        /*      Instrução 8  ->  X = X / Y    */
        firmware[37]  =  0b000000000'100'00011100'000100'000'001'011'100;

        /*      Instrução 4    ->  goto address    */
        firmware[100]  =  0b000000000'100'00010100'001000'001'001'000'010;
        /*    Instrução 10   -> halt      */
        firmware[255] = 0;

        return firmware;
}


#endif

