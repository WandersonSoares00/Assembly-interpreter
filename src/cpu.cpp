
#include "inc/cpu.hpp"


void Cpu :: read_regs(int reg){
    BUS_A = registers.H;
    
    switch (reg){
        case 0:
            BUS_B = registers.MDR;    break;
        case 1:
            BUS_B = registers.PC;    break;
        case 2:
            BUS_B = registers.MBR;    break;
        case 3:
            BUS_B = registers.X;    break;
        case 4:
            BUS_B = registers.Y;    break;
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

void Cpu :: next_instruction(Byte jam){

}

void Cpu :: memory_io(MainMemory *men, Byte memory_bits){

}

void Cpu :: run(){

}
