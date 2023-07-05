#include <iostream>
#include <fstream>
#include "src/inc/memory.hpp"
#include "src/inc/cpu.hpp"
#include "examples/firmware3.hpp"

using namespace std;

int main (int argc, char **argv){
    if (argc <= 1){
        cout << "Memória não informada, sem instruções para executar\n";
        return EXIT_FAILURE;
    }

    MainMemory men;
	Cpu cpu;
    cpu.setMemory(&men);
    Word *firmware = get_firmware();
    cpu.setFirmware(firmware);

    ifstream input (argv[1], ios::in);

    int i = 1;
    men.write_byte (0, 0x00);

    while ( !input.eof() ){
        men.write_byte (i, input.get());
        ++i;
    }

    //men.print_memory(10);

    int time = cpu.start();
    
    cout << "word 1 da memória: " << men.read_word(1) << '\n';
    cout << "word 2 da memória: " << men.read_word(2) << '\n';

	cout << "Execução finalizada em: " << time << " passos\n\n";

    //men.print_memory(8);
    
    delete[] firmware;
    return EXIT_SUCCESS;
}

