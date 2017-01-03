#include "../common.h"

namespace day9b {
	uint64_t decompressed_length(const std::string& input) {
		uint64_t length = 0;
		std::istringstream stream(input);
		char dummy;
		std::string next;
		while(stream >> dummy) {
			if(dummy == '(') {
				int x, y;
				if(!(stream >> x >> dummy >> y >> dummy)) {
					break;
				}
				next.resize(x);
				if(!stream.read(const_cast<char*>(next.data()), x)) {
					break;
				}
				length += decompressed_length(next) * y;
			} else {
				++length;
			}
		}
		return length;
	}

	void run() {
		std::string input = read_file("input/day9.txt");
		std::cout << "day9b ";
		std::cout << decompressed_length(input) << '\n';
		//std::cout << decompressed_length("(3x3)XYZ") << '\n';
		//std::cout << decompressed_length("X(8x2)(3x3)ABCY") << '\n';
		//std::cout << decompressed_length("(27x12)(20x12)(13x14)(7x10)(1x12)A") << '\n';
		//std::cout << decompressed_length("(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN") << '\n';
	}
}