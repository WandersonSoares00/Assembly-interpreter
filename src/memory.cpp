#include <iostream>
#include "inc/memory.hpp"

//std::array<Word32, 1024 * 1024 / 4> memory = {};

Word MainMemory :: read_word(Word addr){
    addr &= 0b111111111111111111; // 18 bits para representar os pinos de endereçamento (2^(18)= 262.144 )
    return memory[addr];
}

void MainMemory :: write_word(Word addr, Word value){
    addr &= 0b111111111111111111; // OBS
    value &= 0xFFFFFFFF; // 8 F's
    memory[addr] = value;
}

// retorna o conteúdo do byte bt da memória principal
Byte MainMemory :: read_byte(unsigned long int bt){
    bt &= 0b11111111111111111111;     //18 1's   (+2)
    Word word_addr = bt >> 2;           // bt / 4
    Word val_word = memory[word_addr];
    
    Byte bt_pos = bt & 0b11;         // resto da divisão por 4
    Word val_byte = val_word >> (bt_pos << 3);  //desloca o valor do byte até a posição mais à esquerda

    val_byte = val_byte & 0xFF;               //  zera o restante

    return val_byte;
}

// escreve no byte "bt" da memória o byte value
// 262.144 * 4 = 1048576(100000000000000000000) bytes possíveis para escrita
void MainMemory :: write_byte(unsigned long int bt, unsigned long int value){
    bt &= 0b11111111111111111111; //(+1)
    value &= 0xFF;
    Word word_addr = bt >> 2;           // bt / 4
    
    Word word_val = memory[word_addr];

    Byte bt_pos = bt & 0b11;         // resto da divisão por 4

    // desloca 1 byte até a posição alvo na palavra onde bt está localizado
    Word mask = 0xFF << (bt_pos << 3);  // 0xFF << (bt_pos * 8)
    mask = ~mask;                       // deixa zerado o espaço do byte onde value será escrito
    
    word_val &= mask;
    
    value <<= (bt_pos << 3);    //  value <<= (bt_pos * 8);
    
    memory[word_addr] = word_val | value;
}


