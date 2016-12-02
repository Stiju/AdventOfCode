#include "../common.h"

namespace day1a {
	struct OpCode {
		int dir, number;
	};

	std::istream& operator >> (std::istream& is, OpCode& opcode) {
		char dummy;
		is >> dummy >> opcode.number;
		opcode.dir = dummy == 'R' ? 1 : -1;
		if(!is.eof()) {
			is >> dummy;
		}
		return is;
	}

	struct BunnyHunter {
		int x, y, direction;

		void turn(int dir) {
			direction += dir;
			if(direction < 0) {
				direction += 4;
			} else if(direction > 3) {
				direction -= 4;
			}
		}

		void move(int blocks) {
			if(direction == 0) {
				y += blocks;
			} else if(direction == 1) {
				x += blocks;
			} else if(direction == 2) {
				y -= blocks;
			} else {
				x -= blocks;
			}
		}
	};

	int calculate_distance(const std::string& input) {
		std::istringstream stream(input);
		OpCode opcode;
		BunnyHunter hunter{0,0,0};
		while(stream >> opcode) {
			hunter.turn(opcode.dir);
			hunter.move(opcode.number);
		}
		return std::abs(hunter.x) + std::abs(hunter.y);
	}

	void run() {
		std::string input = read_file("input/day1.txt");
		std::cout << "day1a ";
		std::cout << calculate_distance(input) << '\n';
		//std::cout << calculate_distance("R2, L3") << '\n';
		//std::cout << calculate_distance("R2, R2, R2") << '\n';
		//std::cout << calculate_distance("R5, L5, R5, R3") << '\n';
	}
}