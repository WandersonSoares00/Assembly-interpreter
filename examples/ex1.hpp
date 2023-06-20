

// Escreva um programa que some o valor da posição de memória 0 com a posição 1 e escreva o resultado na posição 3

/*
    formato de microinstrução (de 32 bits):
    próxima instrução: 9 bits
    jump: 3 bits
    operação na ula: 8 bits
    barramento c: 6 (mar, mdr, pc, x, y, h)
    operação de memória: 3 bits (wr, rd, ft) (wr: memory[mar] = mdr)
    barramento b: 3 bits (0: mdr, 1: pc, 2: mbr, 3: x, 4: y, 5-7: nenhum)

    -------- Formato :  --------
    unsigned long int* get_firmware (){
        long int *firmware = new unsigned long int[512];

        (...)   --sua implementação aqui

        return firmware;
    }
*/


unsigned long int* get_firmware (){
        unsigned long int *firmware = new unsigned long int[512];

        firmware[0] = 0b000000001'000'01110101'000100'010'011; // mdr = men[mar], bus_b = x, ++bus_b, bus_b<<1, x = bus_b (x = 2)
        firmware[1] = 0b000000010'000'00000000'000000'000'000; // bus_b = mdr
        firmware[2] = 0b000000011'000'00010100'000001'000'111; // bus_a = bus_b

        firmware[3] = 0b000000100'000'00110001'100000'010'111; // mar = 1, mdr = men[mar]
        firmware[4] = 0b000000101'000'00110101'100000'000'011; // bus_b = x, ++bus_b, mar = bus_b (mar = 3)
        firmware[5] = 0b000000110'000'00000000'000000'000'000; // bus_b = mdr

        firmware[6] = 0b111111111'000'00111100'010000'100'000; // bus_c = bus_b(mdr) + bus_a, mdr = bus_c, men[3] = mdr, halt
        
        firmware[511] = 0;  // halt

        return firmware;
}



