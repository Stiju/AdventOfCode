#include "../common.h"

namespace day9a {
	uint32_t decompressed_length(const std::string& input) {
		uint32_t length = 0;
		std::istringstream stream(input);
		char dummy;
		while(stream >> dummy) {
			if(dummy == '(') {
				int x, y;
				if(!(stream >> x >> dummy >> y >> dummy)) {
					break;
				}
				stream.ignore(x);
				length += x * y;
			} else {
				++length;
			}
		}
		return length;
	}

	void run() {
		std::string input = read_file("input/day9.txt");
		std::cout << "day9a ";
		std::cout << decompressed_length(input) << '\n';
		//std::cout << decompressed_length("ADVENT") << '\n';
		//std::cout << decompressed_length("A(1x5)BC") << '\n';
		//std::cout << decompressed_length("(3x3)XYZ") << '\n';
		//std::cout << decompressed_length("A(2x2)BCD(2x2)EFG") << '\n';
		//std::cout << decompressed_length("(6x1)(1x3)A") << '\n';
		//std::cout << decompressed_length("X(8x2)(3x3)ABCY") << '\n';
	}
}