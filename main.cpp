#include <iostream>
#include "src/inc/memory.hpp"

using namespace std;

int main(){
	MainMemory men;

	//men.write_byte(30, 55);
	men.write_byte(101, 78);
	cout << men.read_word(25);
	cout << men.read_byte(30) << '\n';
	cout << men.read_byte(9) << '\n';

	return EXIT_SUCCESS;
}
