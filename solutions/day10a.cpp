#include "../common.h"

namespace day10a {
	const short kOutputBit = 1 << 14;
	struct Bot {
		int low, high;
		void insert_value(int value) {
			if(low == 0 || value < low) {
				if(high == 0) {
					high = low;
				}
				low = value;
			} else {
				high = value;
			}
		}
		void give_low(Bot& to) {
			to.insert_value(low);
			low = 0;
		}
		void give_high(Bot& to) {
			to.insert_value(high);
			high = 0;
		}
		bool has_two_microchips() const {
			return low != 0 && high != 0;
		}
	};

	enum class Instructions : bool {
		Set, Give
	};

	struct OpCode {
		bool executed;
		Instructions instruction;
		short from, to_low, to_high;
	};

	std::istream& operator >> (std::istream& is, OpCode& opcode) {
		std::string line;
		if(is >> line) {
			opcode.executed = false;
			if(line == "value") {
				opcode.instruction = Instructions::Set;
				is >> opcode.to_low;
				is.ignore(sizeof("goes to bot"));
				is >> opcode.from;
			} else {
				opcode.instruction = Instructions::Give;
				is >> opcode.from;
				is.ignore(sizeof("gives low to"));
				is >> line >> opcode.to_low;
				if(line == "output") {
					opcode.to_low |= kOutputBit;
				}
				is.ignore(sizeof("and high to"));
				is >> line >> opcode.to_high;
				if(line == "output") {
					opcode.to_high |= kOutputBit;
				}
			}
		}
		return is;
	}

	auto get_instructions(const std::string& input) {
		std::vector<OpCode> ret;
		std::istringstream stream(input);
		OpCode opcode;
		while(stream >> opcode) {
			ret.emplace_back(opcode);
		}
		return ret;
	}

	auto run_instructions(const std::string& input, int low, int high) {
		int bot_id = 0;
		std::unordered_map<short, Bot> bots;
		auto ops = get_instructions(input);
		while(!ops.empty()) {
			for(auto it = ops.begin(); it != ops.end(); ++it) {
				auto& from = bots[it->from];
				if(it->instruction == Instructions::Set) {
					from.insert_value(it->to_low);
					it->executed = true;
				} else if(from.has_two_microchips()) {
					if(from.low == low && from.high == high) {
						bot_id = it->from;
					}
					from.give_low(bots[it->to_low]);
					from.give_high(bots[it->to_high]);
					it->executed = true;
				}
			}
			ops.erase(std::remove_if(ops.begin(), ops.end(), [](const auto& a) {return a.executed; }), ops.end());
		}
		return std::make_pair(bot_id, bots[kOutputBit].low * bots[kOutputBit + 1].low * bots[kOutputBit + 2].low);
	}

	void run() {
		std::string input = read_file("input/day10.txt");
		auto result = run_instructions(input, 17, 61);
		std::cout << "day10a " << result.first << "\nday10b " << result.second << '\n';
		//		auto test = run_instructions(
		//			R"(value 5 goes to bot 2
		//bot 2 gives low to bot 1 and high to bot 0
		//value 3 goes to bot 1
		//bot 1 gives low to output 1 and high to bot 0
		//bot 0 gives low to output 2 and high to output 0
		//value 2 goes to bot 2)", 2, 5);
		//		std::cout << "day10a " << test.first << "\nday10b " << test.second << '\n';
	}
}