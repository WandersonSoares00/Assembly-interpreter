
/*
    *Implementação de um computador de propósito geral, segue o conjunto de instruções:
    * 1) main: PC <- PC + 1; MBR <- read_byte(PC); GOTO MBR
    * 2) X = X + mem[address]
    * 3) mem[address] = X
    * 4) goto address
    * 5) if X = 0 then goto address
    * 6) X = X - mem[address]
    * 7) halt
*/

unsigned long int* get_firmware (){
        unsigned long int *firmware = new unsigned long int[512];

        // incrementa pc, carrega o endereço da instrução no mbr e vai executar a instrução(goto mbr)
        firmware[0] =   0b000000000'100'00110101'001000'001'001;

        // ##2: PC <- PC + 1; MBR <- read_byte(PC); GOTO 3
        // ##3: MAR <- MBR; read_word; GOTO 4
        // ##4: H <- MDR; GOTO 5
        // ##5: X <- H + X; GOTO 0

        firmware[2] =   0b000000011'000'00110101'001000'001'001;
        firmware[3] =   0b000000100'000'00010100'100000'010'010;
        firmware[4] =   0b000000101'000'00010100'000001'000'000;
        firmware[5] =   0b000000000'000'00111100'000100'000'011;

        firmware[255] = 0;    // 7

        return firmware;
}

