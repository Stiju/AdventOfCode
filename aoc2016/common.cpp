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
