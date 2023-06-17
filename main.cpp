#include <iostream>
#include "src/inc/memory.hpp"

using namespace std;

int main(){
	MainMemory men;

	//men.write_byte(103, 55);
	men.write_byte(101, 78);

	cout << bin<4>(men.memory[25]) << '\n';
	//cout << men.read_word(25) << '\n';
	cout << men.read_byte(101) << '\n';

	return EXIT_SUCCESS;
}
