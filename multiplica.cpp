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
	
	men.write_word(5, 0);		//men[5] = 8
	men.write_word(6, 15);		//men[6] = 15
	men.write_word(7, 1);		//men[7] = 1	// dec
	men.write_word(8, 0);		//men[8]		// aux
	men.write_word(9, 0);		//men[9]		// result

	men.write_byte(1, 2);
	men.write_byte(2, 5); // add x, men[5]

	men.write_byte(3, 11);
	men.write_byte(4, 255);	// pula halt

	men.write_byte(5, 13);
	men.write_byte(6, 7); // x-1

	men.write_byte(7, 6);
	men.write_byte(8, 5); //mov x, 8

	men.write_byte(9, 2);
	men.write_byte(10, 6); //add x, men[6]

	men.write_byte(11, 6);
	men.write_byte(12, 9); //mov x, men[9]

	men.write_byte(13, 9);
	men.write_byte(14, 1);

	
	int time = cpu.start(true);
	cout << "Execução finalizada em: " << time << " passos\n";

	cout << men.read_word(9) << '\n';
	//cout << cpu.registers.X << '\n';

	delete[] firmware;

	return EXIT_SUCCESS;
}

