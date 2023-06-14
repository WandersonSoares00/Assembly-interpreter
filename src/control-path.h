#ifndef CONTROL-PATH
#define CONTROL-PATH

//structure instruction
//next_add |jmpc|jamn||jamz|sll8|sra1|f0|f1|enA|enB|invA|inc|h|opc|tos|cpp|lv|sp|pc|mdr|mar|write|read|fetch|B_bus|

typedef unsigned char Byte;

//  typedef Byte Word8;   // palavra de dados de 8 bits

typedef Byte Word32[4];   // palavra de dados(de 32 bits) da memória

// 5 bits p/ prox instrução + 3 jump + 8 p/ ALU + 9 p/ BUS_C + 3 p/ memória principal + 4 p/ BUS_B
Word32 control_memory[32];
Word32 MPC;
Word32 MIR;     //29 bits usáveis (- 3 bits p/ RAM)

Word32 BUS_A;
Word32 BUS_B;
Word32 BUS_C;

















#endif