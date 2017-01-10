#include "common.h"
#include <fstream>

std::string read_file(const char* filename) {
	std::string content;
	std::ifstream file(filename, std::ios::binary);
	if(!file) {
		std::cout << filename << " not found\n";
		std::exit(EXIT_FAILURE);
	}
	file.seekg(0, std::ios::end);
	content.resize(static_cast<size_t>(file.tellg()));
	file.seekg(0, std::ios::beg);
	file.read(&content[0], content.size());
	return content;
}

void homemade_itoa(int value, char* str) {
	char buffer[12];
	char* p = &buffer[11];
	*p = 0;
	do {
		*--p = '0' + value % 10;
		value /= 10;
	} while(value);
	std::memcpy(str, p, &buffer[12] - p);
}