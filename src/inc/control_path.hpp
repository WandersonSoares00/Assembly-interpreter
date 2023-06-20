#ifndef CONTROL_PATH_HPP
#define CONTROL_PATH_HPP

//structure instruction
//next_add |jmpc|jamn||jamz|sll8|sra1|f0|f1|enA|enB|invA|inc|h|opc|tos|cpp|lv|sp|pc|mdr|mar|write|read|fetch|B_bus|
typedef unsigned char Byte;

//  typedef Byte Word8;   // palavra de dados de 8 bits

typedef unsigned long int Word;   // palavra de dados(de  bits) da memória

/*
// 5 bits p/ prox instrução + 3 jump + 8 p/ ALU + 9 p/ BUS_C + 3 p/ memória principal + 4 p/ BUS_B
//Word control_memory[];

     //29 bits usáveis (- 3 bits p/ RAM)

Word BUS_A;
Word BUS_B;
Word BUS_C;

*/

#endif