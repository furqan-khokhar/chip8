#include <iostream>

#include "cpu.h"
#include <bitset>

// Decode Macros
#define X hi & 0x0F						//	-X--
#define Y (lo & 0xF0) >> 4				//	--Y-
#define N lo & 0x0F						//	---N
#define NN lo							//	--NN
#define NNN (hi << 8 | lo) & 0x0FFF		//	-NNN

#define VX v[X]
#define VY v[Y]
#define VF v[0xF]

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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			gfx[i][j] = 0;
		}
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
	//printf("%x : %2.2x\n", pc, hi & 0xFF);
	pc++;
	lo = ram[pc];
	//printf("%x : %2.2x\n", pc, lo & 0xFF);
	pc++;
	//printf("x: %1.1x, y: %1.1x, n: %1.1x, nn: %2.2x, nnn: %3.3x\n", X, Y, N, NN, NNN);
	printf("%2.2x%2.2x\n", hi & 0xFF, lo & 0xFF);

	// Decode

	switch (hi >> 4) {
		case 0x0:
			switch (hi << 8 | lo) {
				case 0x00E0:
					// Clear screen
					for (int row = 0; row < rows; row++) {
						for (int col = 0; col < columns; col++) {
							gfx[row][col] = 0;
						}
					}
					break;

				case 0x00EE:
					// Return from subroutine
					pc = stack[sp];		// Set PC to stack value
					stack[sp--] = NULL;	// Pop last address from stack
					break;
			}
			break;

		case 0x1:
			// 1NNN
			// Jump
			pc = NNN;	// PC jumps to NNN
			break;

		case 0x2:
			// 2NNN
			// Jump to subroutine
			
			// Check for stack overflow
			if (sp >= ( sizeof(stack)/sizeof(stack[0]))) {
				throw std::runtime_error("Stack overflow\n");
			}

			stack[sp++] = pc;	// Push current PC to stack
			pc = NNN;			// PC jumps to NNN
			break;

		//case 0x3:
		//	break;

		//case 0x4:
		//	break;

		//case 0x5:
		//	break;

		case 0x6:
			// 6XNN
			// Set VX to NN
			VX = NN;
			break;

		case 0x7:
			// 7XNN
			// Add NN to VX
			VX += NN;
			break;

		//case 0x8:
		//	break;

		//case 0x9:
		//	break;

		case 0xA:
			// ANNN
			// Set i to NNN
			i = NNN;
			break;

		//case 0xB:
		//	break;

		//case 0xC:
		//	break;

		case 0xD:
			uint8_t x = VX % columns;
			uint8_t y = VY % rows;
			uint8_t sprite_height = N;
			VF = 0;

			for (uint8_t row = 0; row < sprite_height; row++) {
				uint8_t sprite_row = ram[i + row];
				
				for (uint8_t col = 0; col < 8; col++) {
					uint8_t sprite_pixel = sprite_row & (0x80 >> col);
					uint8_t *display_pixel = &gfx[y + row][x + col];

					if (sprite_pixel && display_pixel) {
						VF = 1;
					}

					*display_pixel ^= sprite_pixel;
				}
			}

			break;

		//case 0xE:
		//	break;

		//case 0xF:
		//	break;

		//default:
		//	break;
	}

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

void Cpu::print_display( std::ostream& out ) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (gfx[i][j]) {
				out << "#";
			}
			else {
				out << " ";
			}
		}
		out << "\n";
	}
}