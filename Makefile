PROJ_NAME = comp
CXX = g++
CPPFLAGS = -Wall -Wextra -std=c++17 -pedantic
RM = rm -rf
OBJ_DIR = bin

all: $(OBJ_DIR) $(PROJ_NAME) assembler

$(PROJ_NAME):	$(OBJ_DIR)/computer.o $(OBJ_DIR)/memory.o $(OBJ_DIR)/cpu.o
	$(CXX) $(CPPFLAGS) $^  -o $(PROJ_NAME)

$(OBJ_DIR)/computer.o:	computer.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/memory.o: src/memory.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/cpu.o:	src/cpu.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

assembler:
	$(CXX) $(CPPFLAGS) src/assembler.cpp  -o assembler

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR) $(PROJ_NAME)
