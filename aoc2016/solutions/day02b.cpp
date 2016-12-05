#include "../common.h"

namespace day2b {
	const int width = 5;
	const char keypad[] = {
		0, 0, 1, 0, 0,
		0, 2, 3, 4, 0,
		5, 6, 7, 8, 9,
		0,10,11,12, 0,
		0, 0,13, 0, 0
	};

	struct Position {
		int x, y;
	};

	bool is_valid(int x, int y) {
		if(x < 0 || y < 0 || x > 4 || y > 4) {
			return false;
		}
		return keypad[x + y * width] != 0;
	}

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
		Position position{0,2};
		int code = 0;
		int i = 1;
		while(stream >> line) {
			const char* p = line.c_str();
			while(*p) {
				switch(*p++) {
				case 'U': if(is_valid(position.x, position.y - 1)) --position.y; break;
				case 'R': if(is_valid(position.x + 1, position.y)) ++position.x; break;
				case 'D': if(is_valid(position.x, position.y + 1)) ++position.y; break;
				case 'L': if(is_valid(position.x - 1, position.y)) --position.x; break;
				}
			}
			code += keypad[position.x + position.y * width] * i;
			i *= 16;
		}
		return reverse(code, 16);
	}

	void run() {
		std::string input = read_file("input/day2.txt");
		std::cout << "day2b ";
		std::cout << std::hex << get_bathroom_code(input) << '\n';
		//std::cout << std::hex << get_bathroom_code("ULL\nRRDDD\nLURDL\nUUUUD") << '\n';
		std::cout << std::dec;
	}
}