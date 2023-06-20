#include <iostream>
#include "src/inc/memory.hpp"
#include "src/inc/cpu.hpp"

using namespace std;

int main(){
	MainMemory men;
	Cpu cpu;

	men.write_word(0, 12);
	men.write_word(1, 37);

	//cpu.setFirmware();

	cout << "Execução finalizada em: " << cpu.start() << '\n';

	cout << men.read_word(3) << '\n';

	return EXIT_SUCCESS;
}

