
#include "inc/cpu.hpp"

void Cpu :: setFirmware(Word *firm){
    firmware = firm;
}

void Cpu :: read_regs(int reg){
    BUS_A = registers.H;
    
    switch (reg){
        case 0:
            BUS_B = registers.MDR;   break;
        case 1:
            BUS_B = registers.PC;    break;
        case 2:
            BUS_B = registers.MBR;   break;
        case 3:
            BUS_B = registers.X;     break;
        case 4:
            BUS_B = registers.Y;     break;
        default:
            BUS_B = 0;
    }
}

void Cpu :: write_regs(int reg_bits){   //6 bits de seleção
    if (reg_bits & 0b100000)    
		registers.MAR = BUS_C;
	if (reg_bits & 0b010000)
		registers.MDR = BUS_C;
	if (reg_bits & 0b001000)
		registers.PC = BUS_C;
	if (reg_bits & 0b000100)
		registers.X = BUS_C;
	if (reg_bits & 0b000010)
		registers.Y = BUS_C;
	if (reg_bits & 0b000001)
		registers.H = BUS_C;
}

Word Cpu :: shifter(Word alu_out, short int select_bits){
    switch(select_bits){
        case 0b01:
            return alu_out << 1;
        case 0b10:
            return alu_out >> 1;
        case 0b11:
            return alu_out << 8;
        default:
            return alu_out;
    }   
}

void Cpu :: alu(long int control_bits){
    short int shift_bits = control_bits & 0b11000000;
    shift_bits = shift_bits >> 6;

    Word in_a = registers.H;
    Word in_b = BUS_B;
    Word out = 0;

    switch(control_bits){
        case 0b011000:
            out = in_a;             break;
        case 0b010100:
            out = in_b;             break;
        case 0b011010:
            out = ~in_a;            break;
        case 0b101100:
            out = ~in_b;            break;
        case 0b111100:
            out = in_a + in_b;      break;
        case 0b111101:
            out = in_a + in_b + 1;  break;
        case 0b111001:
            out = in_a + 1;         break;
        case 0b110101:
            out = in_b + 1;         break;
        case 0b111111:
            out = in_b - in_a;      break;
        case 0b110110:
            out = in_b - 1;         break;
        case 0b111011:
            out = -in_a;            break;
        case 0b001100:
            out = in_a & in_b;      break;
        case 0b011100:          
            out = in_a | in_b;      break;
        case 0b010000:
            out = 0;                break;
        case 0b110001:
            out = 1;                break;
        case 0b110010:  
            out = -1;               break;

    }
	if (out == 0){
		N = 0;
		Z = 1;
    }
	else{
		N = 1;
		Z = 0;
    }

    BUS_C = shifter(out, shift_bits);
}

void Cpu :: next_instruction(Word next_inst, Byte jmpc){

    if (jmpc == 0b000){
        MPC = next_inst;
        return;
    }

    if (jmpc & 0b001){   // jamz
        next_inst |= (Z << 8);
    }

    if (jmpc & 0b010){  //jamn
        next_inst |= (N << 8);
    }

    if (jmpc & 0b100){  // próxima instrução vem da memória principal
        next_inst |= registers.MBR;
    }

    MPC = next_inst;
}

void Cpu :: memory_io(MainMemory *men, Byte memory_bits){
    
    if (memory_bits & 0b001)  //fetch
        registers.MBR = men -> read_byte(registers.PC);
    if (memory_bits & 0b010)  //read
        registers.MBR = men -> read_word(registers.MAR);
    if (memory_bits & 0b100)  //write
        men -> write_word(registers.MAR, registers.MDR);
}

bool Cpu :: run(){
    MIR = firmware[MPC];

    if (MIR == 0)   //quit
        return false;
    
    read_regs        ( MIR & 0b11);
    alu              ((MIR & 0b11111111000000000000) >> 12);
    write_regs       ((MIR & 111111000000) >> 6);
    next_instruction ((MIR & 0b11111111100000000000000000000000) >> 23, (MIR & 0b11100000000000000000000) >> 20);

    return true;
}

int Cpu :: start(){
    int count = 0;

    while (true){
        if ( run() )        ++count;
        else                break;
    }

    return count;
}
