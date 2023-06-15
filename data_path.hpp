#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include "control_path.hpp"

typedef struct Register_bank{
    Word SP;
    Word LV;
    Word CPP;
    Word TOS;
    Word OPC;
    Word H;
    /*  Interface com memória   */
    //ler/escrever palavras de dados pertencentes ao nível ISA
    Word MAR;
    Word MDR;
    //ler o programa executável, grupo de bytes, do nível ISA
    Word PC;
    Word MBR;
}Reg_bank;


#endif
