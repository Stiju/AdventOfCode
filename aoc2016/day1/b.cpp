#include "../common.h"

namespace day1b {
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
		union {
			struct {
				int x, y;
			} coords;
			uint64_t hash;
		} position;
		int direction;

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
				position.coords.y += blocks;
			} else if(direction == 1) {
				position.coords.x += blocks;
			} else if(direction == 2) {
				position.coords.y -= blocks;
			} else {
				position.coords.x -= blocks;
			}
		}
	};

	int calculate_distance(const std::string& input) {
		std::istringstream stream(input);
		OpCode opcode;
		BunnyHunter hunter{0,0,0};
		std::unordered_set<uint64_t> visited;
		visited.insert(hunter.position.hash);
		while(stream >> opcode) {
			hunter.turn(opcode.dir);
			while(opcode.number--) {
				hunter.move(1);
				if(!visited.insert(hunter.position.hash).second) {
					goto end_loop;
				}
			}
		}
		end_loop:
		return std::abs(hunter.position.coords.x) + std::abs(hunter.position.coords.y);
	}

	void run() {
		std::string input = read_file("input/day1.txt");
		std::cout << "day1b ";
		std::cout << calculate_distance(input) << '\n';
		//std::cout << calculate_distance("R8, R4, R4, R8") << '\n';
	}
}