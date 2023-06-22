#include <iostream>
#include "src/inc/memory.hpp"
#include "src/inc/cpu.hpp"
#include "examples/firmware.hpp"

using namespace std;

int main(){
		MainMemory men;
		Cpu cpu;
		cpu.setMemory(&men);
		Word *firmware = get_firmware();
		cpu.setFirmware(firmware);
	
	men.write_word(50, 80);		//men[50] = 80
	men.write_word(100, 15);	//men[100] = 15

	// x = x + men[50]
	men.write_byte(1, 2);	// operando 2: soma
	men.write_byte(2, 50);	// 50 é o endereço de men[50]

	// x = x + men[100]
	men.write_byte(3, 2);
	men.write_byte(4, 100);

	//cout << bin <8> (men.read_byte(4)) << '\n';
	
	int time = cpu.start(true);
	cout << "Execução finalizada em: " << time << " passos\n";

	cout << cpu.registers.X << '\n';

	delete[] firmware;

	return EXIT_SUCCESS;
}

