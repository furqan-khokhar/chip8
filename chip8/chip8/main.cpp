#include <iostream>
#include <stdint.h>

#include "cpu.h"

int main() {
	
	Cpu cpu = Cpu();	// Initialise chip8 cpu

	uint8_t bytes_read;	// File size

	// Execute every operand in file
	// Each operand is 1 nibble

	for (int i = 0; i < bytes_read/2; i++) {
		cpu.tick();
	}

}