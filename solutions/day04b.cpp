#include "../common.h"

namespace day4b {
	void decipher_name(std::string& name, int id) {
		for(size_t i = 0; i < name.size(); ++i) {
			char c = name[i];
			if(c == '-') {
				continue;
			}
			name[i] = 'a' + ((id + c - 'a') % 26);
		}
	}

	int northpole_room_id(const std::string& input) {
		std::istringstream stream(input);
		std::string line;
		while(stream >> line) {
			std::string name{line.begin(), line.end() - 11};
			int id = std::stoi(std::string{line.end() - 10, line.end() - 7});
			decipher_name(name, id);
			if(name == "northpole-object-storage") {
				return id;
			}
		}
		return 0;
	}

	void run() {
		std::string input = read_file("input/day4.txt");
		std::cout << "day4b ";
		std::cout << northpole_room_id(input) << '\n';
	}
}