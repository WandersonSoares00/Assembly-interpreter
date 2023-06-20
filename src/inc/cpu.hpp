#ifndef CPU_H
#define CPU_H

#include "control_path.hpp"
#include "memory.hpp"

typedef struct Register_bank{
    Word PC = 0;
    Word MDR = 0;
    Word MBR = 0;
    Word MAR = 0;
    Word H = 0;
    Word MIR = 0;

    Word X = 0, Y = 0;
    
    Word SP = 0;
    Word LV = 0;
    Word CPP = 0;
    Word TOS = 0;
    Word OPC = 0;
}Reg_bank;

struct Cpu{
    // -------- Banco de registradores --------
    Reg_bank registers;
    Byte N = 0;
    Byte Z = 1;
    // --------- Barramentos ------------------
    Word BUS_A = 0;
    Word BUS_B = 0;
    Word BUS_C = 0;
    // --------- Memória de controle ----------
    Word firmware[512];
    
    void read_regs(int reg);
    void write_regs(int reg_bits);  // reg_bits = C
    Word shifter(Word alu_out, short int select_bits);
    void alu(long int control_bits);
    void next_instruction(Byte jam);
    
    void memory_io(MainMemory *men, Byte memory_bits);
    void run();
};


#endif







