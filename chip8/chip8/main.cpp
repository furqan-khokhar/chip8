#include <iostream>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <filesystem>

#include "cpu.h"

auto read_file_data(const char* file_path) noexcept -> std::vector<char> {
	std::vector<char> file_data{};

	std::ifstream input_file(file_path, std::ios::binary);

	auto size = std::filesystem::file_size(file_path);

	std::istreambuf_iterator<char> input_reader{ input_file }, end;

	file_data.assign(input_reader, end);

	input_file.close();

	return file_data;
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "[ * ] Load Chip8 ROM with program.\n";
		return 1;
	}

	std::vector<char> file_data = read_file_data(argv[1]);
	
	Cpu cpu = Cpu();	// Initialise chip8 cpu	

	int bytes_read = file_data.size();	// File size

	printf("%.x\n",  bytes_read);

	// Read ROM (debugging, clean & delete later)
	
	/*
	for (unsigned int i : file_data)
		printf("%2.2x ", i & 0xFF);
		std::cout << std::endl;
	*/

	cpu.load(file_data.data(), bytes_read);

	// Execute every operand in file
	// Each operand is 1 nibble

	for (int i = 0; i < bytes_read/2; i++) {
		cpu.tick();
	}

}