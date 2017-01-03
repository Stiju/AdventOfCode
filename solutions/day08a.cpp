#include "../common.h"

namespace day8a {
	enum class Instructions {
		Rect, Row, Column
	};
	struct OpCode {
		Instructions instruction;
		int x, y;
	};

	std::istream& operator >> (std::istream& is, OpCode& opcode) {
		char dummy;
		std::string line;
		is >> line;
		if(line == "rect") {
			opcode.instruction = Instructions::Rect;
			is >> opcode.x >> dummy >> opcode.y;
		} else {
			is >> line;
			opcode.instruction = line == "row" ? Instructions::Row : Instructions::Column;
			is >> dummy >> dummy >> opcode.x >> line >> opcode.y;
		}
		return is;
	}

	template<int width, int height>
	class Display {
		static const int width_size = width + 1;
		char display[width_size * height];
	public:
		Display() {
			std::memset(display, '.', width_size * height);
			for(int i = 0; i < height - 1; ++i) {
				display[width + i * width_size] = '\n';
			}
			display[width_size * height - 1] = 0;
		}
		void set_rect(const OpCode& opcode) {
			for(int y = 0; y < opcode.y; ++y) {
				for(int x = 0; x < opcode.x; ++x) {
					display[x + y * width_size] = '#';
				}
			}
		}
		void shift_right(const OpCode& opcode) {
			char row_buffer[width];
			for(int i = 0; i < width; ++i) {
				row_buffer[((i + opcode.y) % width)] = display[i + opcode.x * width_size];
			}
			std::memcpy(&display[opcode.x * width_size], row_buffer, width);
		}
		void shift_down(const OpCode& opcode) {
			char column_buffer[height];
			for(int i = 0; i < height; ++i) {
				column_buffer[((i + opcode.y) % height)] = display[opcode.x + i * width_size];
			}
			for(int i = 0; i < height; ++i) {
				display[opcode.x + i * width_size] = column_buffer[i];
			}
		}
		const char* data() const {
			return display;
		}
		int lit_pixels() const {
			int lit = 0;
			for(int i = 0; i < width_size * height; ++i) {
				if(display[i] == '#') {
					++lit;
				}
			}
			return lit;
		}
	};

	template<int width, int height>
	void run_instructions(const std::string& input) {
		Display<width, height> display;
		std::istringstream stream(input);
		OpCode opcode;
		while(stream >> opcode) {
			switch(opcode.instruction) {
			case Instructions::Rect: display.set_rect(opcode); break;
			case Instructions::Row: display.shift_right(opcode); break;
			case Instructions::Column: display.shift_down(opcode); break;
			}
		}
		std::cout << display.lit_pixels() << '\n' << display.data() << '\n';
	}

	void run() {
		std::string input = read_file("input/day8.txt");
		std::cout << "day8a ";
		run_instructions<50, 6>(input);
		//run_instructions<7, 3>("rect 3x2\nrotate column x=1 by 1\nrotate row y=0 by 4\nrotate column x=1 by 1");
	}
}