#ifndef COMMON_HPP
#define COMMON_HPP

#include <bitset>

template<int Q = 8, typename T>
std::bitset<sizeof(T) * Q> bin(T number) {
    std::bitset<sizeof(T) * Q> binary(number);
    return binary;
}

typedef unsigned char Byte;

typedef long int Word;

#endif