#include "../common.h"

namespace day2a {
	const int width = 3;
	const char keypad[] = {1,2,3,4,5,6,7,8,9};

	struct Position {
		int x, y;
	};

	int reverse(int value, int base) {
		int result = 0;
		while(value > 0) {
			result = result * base + (value % base);
			value /= base;
		}
		return result;
	}

	int get_bathroom_code(const std::string& input) {
		std::istringstream stream(input);
		std::string line;
		Position position{1,1};
		int code = 0;
		int i = 1;
		while(stream >> line) {
			const char* p = line.c_str();
			while(*p) {
				switch(*p++) {
				case 'U': if(position.y > 0) --position.y; break;
				case 'R': if(position.x < 2) ++position.x; break;
				case 'D': if(position.y < 2) ++position.y; break;
				case 'L': if(position.x > 0) --position.x; break;
				}
			}
			code += keypad[position.x + position.y * width] * i;
			i *= 10;
		}
		return reverse(code, 10);
	}

	void run() {
		std::string input = read_file("input/day2.txt");
		std::cout << "day2a ";
		std::cout << get_bathroom_code(input) << '\n';
		//std::cout << get_bathroom_code("ULL\nRRDDD\nLURDL\nUUUUD") << '\n';
	}
}