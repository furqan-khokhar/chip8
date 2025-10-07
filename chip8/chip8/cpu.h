#ifndef CPU_H
#define CPU_H

#include <stdint.h>					// Standard library for fixed width integer types

class Cpu {
private:
	uint8_t memory[4 * 1024];		// Memory (4 kilobytes)
									// All of chip8's memory is RAM and considered writable

	uint8_t gfx[64 * 32];			// Graphics Buffer
									// 64 x 32 pixel resolution
									// Each byte represents 1 pixel, allows for colours in future implementation

	uint16_t pc;					// Program Counter

	uint16_t i;						// Index Register
									// Can only address 12 bits

	uint16_t stack[16];				// Stack
									// Calls subroutines and returns from them

	uint8_t sp;						// Stack Pointer
									// Points to next free slot in stack

	uint8_t delay_timer;			// Delay Timer
									// Decremented at 60Hz until it reaches 0

	uint8_t sound_timer;			// Sound Timer
									// Decremented at 60Hz until it reaches 0
									// Beeps if not at 0

	uint8_t v[16];					// Variable Registers
									// Numbered 0 through F
									// VF is used as a flag register

	uint16_t opcode;				// Opcode
									// Instructions/data to be processed
	
	void init();

public:
	Cpu();

	void tick();
	bool load(uint8_t rom[]);
};

#endif