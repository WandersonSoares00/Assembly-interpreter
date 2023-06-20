#include <iostream>
#include "src/inc/memory.hpp"
#include "src/inc/cpu.hpp"
#include "examples/ex1.hpp"

using namespace std;

int main(){
	MainMemory men;
	Cpu cpu;

	men.write_word(0, 12);
	men.write_word(1, 37);

	cpu.setMemory(&men);
	Word *firmware = get_firmware();
	cpu.setFirmware(get_firmware());

	int time = cpu.start();
	cout << "Execução finalizada em: " << time << " passos\n";

	cout << men.read_word(3) << '\n';

	delete[] firmware;

	return EXIT_SUCCESS;
}

