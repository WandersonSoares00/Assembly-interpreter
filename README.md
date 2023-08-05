# Assembly-interpreter
---
This is an 32 bit computer architecture simulator that compiles and run a assembly codes defined by the architecture.

## Purpose

The intention of the project is to understand how modern computers works. It's possible define new microinstructions for the computer following the model in [examples/firmware3.hpp](examples/firmware3.hpp), add in the array _instructions_ and set into _set_ops(string& line, unsigned long int &oper)_ function found in [src/assembler/assembler.cpp](src/assembler/assembler.cpp).

## Microarchitecture

The model of microarchitecture is basead on the book Structured Computer Organization by author [Andrew S.Tanenbaum](https://en.wikipedia.org/wiki/Andrew_S._Tanenbaum), the [instruction set](https://simple.wikipedia.org/wiki/Instruction_set#:~:text=An%20instruction%20set%20is%20the,share%20a%20common%20instruction%20set.) can be found in [examples/firmware3](fff).

![Micrcoarchitecture diagram](img/arc.jpg)
Here is an ilustration of the micrcoarchitecture in a diagram.

## Usage
---
### Prerequisites

- GNU C++ Compiler ( g++ )
- GNU Make installed

On debian-based linux distributions, run `sudo apt install make g++
`
### How to run?

1. Clone the repository
    `git clone https://github.com/WandersonSoares00/Assembly-interpreter`

2. Run make
    `make all`

3. Generate a binary of an .asm program with the assembler
    take program [questions/fat.asm](questions/fat.asm) as an example, run the following command:
    `./assembler questions/fat.asm outBin`

4. Copy the binary in memory and run a computer
    `./comp outBin`
    For default, the computer print the word 1 and 2 of memory in the scream to simulate the [standard output](https://en.wikipedia.org/wiki/Standard_streams)

### Licence information
This project is licensed under the GNU General Public License v3.0.
