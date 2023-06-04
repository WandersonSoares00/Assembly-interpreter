#include "control-path.h"

typedef struct Register_bank{
    Word32 SP;
    Word32 LV;
    Word32 CPP;
    Word32 TOS;
    Word32 OPC;
    Word32 H;
    /*  Interface com memória   */
    //ler/escrever palavras de dados pertencentes ao nível ISA
    Word32 MAR;
    Word32 MDR;
    //ler o programa executável, grupo de bytes, do nível ISA
    Byte PC;
    Word8 MBR;
}Reg_bank;



