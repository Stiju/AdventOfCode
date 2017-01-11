#include "../common.h"

namespace day15a {
	int tmp(const std::string& input) {
		std::istringstream stream(input);
		return 0;
	}

	void run() {
		std::string input = read_file("input/day15.txt");
		std::cout << "day15a ";
		std::cout << tmp(input) << '\n';
	}
}