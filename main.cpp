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
	
	//	(par: operação, operando)
	
	// salta para a instrução 5 caso X == 0
	//men.write_byte(1, 11);
	//men.write_byte(2, 5);

	// soma men[50] + men[100]

	men.write_word(50, 80);		//men[50] = 80
	men.write_word(100, 150);	//men[100] = 150

	// x = x + men[50]
	//men.write_byte(1, 2);	// operando 2: soma
	//men.write_byte(2, 50);	// 50 é o endereço de men[50]
	

	// x = x + men[100]
	men.write_byte(3, 2);
	men.write_byte(4, 100);

	// x = x - men[100]
	men.write_byte(5, 13);
	men.write_byte(6, 50);

	//cout << bin <8> (men.read_byte(4)) << '\n';

	men.write_byte(7, 6);	// chama o operando para armazenar X em men[150]
	men.write_byte(8, 150);

	men.write_byte(9, 255);	// halt

	int time = cpu.start(true);
	cout << "Execução finalizada em: " << time << " passos\n";

	cout << men.read_word(150) << '\n';
	//cout << cpu.registers.X << '\n';

	delete[] firmware;

	return EXIT_SUCCESS;
}
