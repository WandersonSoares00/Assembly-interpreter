#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "control_path.hpp"
#include "common.hpp"

struct MainMemory{
    // memória de 1 mbyte, cada palavra consistindo em 4 bytes
    Word memory[ 1024 * 1024 / 4 ] = {0};       // pode endereçar 262.144 palavras

    Word read_word(Word addr);
    void write_word(Word addr, Word value);
    Byte read_byte(unsigned long int bt);
    void write_byte(unsigned long int bt, long int value);
    void print_memory(int words);
};



#endif