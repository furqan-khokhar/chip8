#include <iostream>

#include "cpu.h"

// Decode Macros
#define X hi & 0x0F				//	-X--
#define Y (lo & 0xF0) >> 4		//	--Y-
#define N lo & 0x0F				//	---N
#define NN lo					//	--NN
#define NNN ((hi & 0x0F) | lo)	//	-NNN

#define VX V[X]
#define VY V[Y]
#define VF V[0xF]

// Resets CPU's state
// Will allow for different ROMs to be played without closing and re-opening the program.

void Cpu::init()
{
	std::cout << "Constructor\n";

	pc = 0x200;		// PC starts at index 512
	i = 0;			// Reset index pointer
	sp = 0;			// Reset stack pointer
	opcode = 0;		// Reset opcode

	// Clear RAM
	for (int i = 0; i < 4 * 1024; i++) {
		ram[i] = 0;
	}

	// Clear graphics buffer
	for (int i = 0; i < 64 * 32; i++) {
		gfx[i] = 0;
	}

	// Clear stack and variable registers
	for (int i = 0; i < 16; i++) {
		stack[i] = 0;
		v[i] = 0;
	}

	// Reset timers
	delay_timer = 0;
	sound_timer = 0;
}

// Ensure expected CPU state when initialised

Cpu::Cpu() { init(); }

// Called every FDE cycle

void Cpu::tick()
{
	// Print all opcodes from memory, 2 opcodes are used per tick
	hi = ram[pc];
	printf("%u : %2.2x\n", pc, hi & 0xFF);
	pc++;
	lo = ram[pc];
	printf("%u : %2.2x\n", pc, lo & 0xFF);
	pc++;
	printf("x: %1.1x, y: %1.1x, n: %1.1x, nn: %2.2x, nnn: %3.3x\n", X, Y, N, NN, NNN);

	// Decode & Execute

	// _X__
	// __Y_
	// ___N
	// __NN
	// _NNN
	
}

// Load ROM into emulator

bool Cpu::load(char* rom_pointer, int rom_size)
{
	// Reset CPU state
	init();

	// Add ROM to memory
	for (int i = 0; i < rom_size; ++i) {
		printf("%i : %2.2x ", i, *(rom_pointer + i) & 0xFF);
		ram[pc+i] = *(rom_pointer + i);
		std::cout << std::endl;
	}

	return false;
}