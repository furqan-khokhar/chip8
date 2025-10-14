#include <iostream>

#include "cpu.h"

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
}

// Load ROM into emulator

bool Cpu::load(uint8_t rom[], uint8_t rom_size)
{
	// Reset CPU state
	init();

	return false;
}