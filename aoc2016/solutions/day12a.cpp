#include "../common.h"

namespace day12a {
	enum class OpCode {
		Cpy, Inc, Dec, Jnz
	};

	struct Value {
		int data : 7;
		int is_reg : 1;
	};

	struct Instruction {
		OpCode opcode;
		Value x, y;
	};

	std::istream& operator >> (std::istream& is, Instruction& ins) {
		auto read_value = [](std::istream& is) {
			Value value;
			if(is.ignore(1).peek() < 'A') {
				int tmp;
				is >> tmp;
				value.data = tmp;
				value.is_reg = 0;
			} else {
				value.data = is.get() - 'a';
				value.is_reg = -1;
			}
			return value;
		};
		std::string type;
		if(is >> type) {
			ins.x = read_value(is);
			if(type == "cpy") {
				ins.opcode = OpCode::Cpy;
				ins.y = read_value(is);
			} else if(type == "inc") {
				ins.opcode = OpCode::Inc;
			} else if(type == "dec") {
				ins.opcode = OpCode::Dec;
			} else {
				ins.opcode = OpCode::Jnz;
				ins.y = read_value(is);
			}
		}
		return is;
	}

	auto get_instructions(const std::string& input) {
		std::vector<Instruction> instructions;
		std::istringstream stream(input);
		Instruction ins;
		while(stream >> ins) {
			instructions.emplace_back(ins);
		}
		return instructions;
	}

	int run_instructions(const std::string& input, int c) {
		int registers[4] = {0,0,c,0};
		auto instructions = get_instructions(input);
		size_t size = instructions.size();
		auto ptr = instructions.data(); // speed up debug run
		for(size_t i = 0; i < size;) {
			auto& in = ptr[i];
			switch(in.opcode) {
			case OpCode::Cpy: registers[in.y.data] = in.x.is_reg ? registers[in.x.data] : in.x.data; break;
			case OpCode::Inc: ++registers[in.x.data]; break;
			case OpCode::Dec: --registers[in.x.data]; break;
			case OpCode::Jnz: if(in.x.is_reg ? registers[in.x.data] : in.x.data) { i += in.y.data; goto end; } break;
			}
			++i;
		end:;
		}
		return registers[0];
	}

	void run() {
		std::string input = read_file("input/day12.txt");
		std::cout << "day12a " << run_instructions(input, 0);
		std::cout << "\nday12b " << run_instructions(input, 1) << '\n';
		//std::cout << run_instructions("cpy 41 a\ninc a\ninc a\ndec a\njnz a 2\ndec a", 0) << '\n';
	}
}