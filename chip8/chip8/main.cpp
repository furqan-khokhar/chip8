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

	std::cout << size << std::endl;

	input_file.seekg(0, std::ios::end);

	//std::cout << std::hex << input_file.rdbuf() << std::endl;

	std::istreambuf_iterator<char> input_reader{ input_file }, end;

	file_data.assign(input_reader, {});

	std::string input_text{ input_reader, end };

	input_file.close();

	//std::cout << input_text.size() << std::endl;

	return file_data;
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "[ * ] Load Chip8 ROM\n";
		return 1;
	}

	//char* path = argv[1];

	//std::cout << path << std::endl;

	read_file_data(argv[1]);
	
	Cpu cpu = Cpu();	// Initialise chip8 cpu

	uint8_t bytes_read = 0;	// File size

	// Execute every operand in file
	// Each operand is 1 nibble

	for (int i = 0; i < bytes_read/2; i++) {
		cpu.tick();
	}

}