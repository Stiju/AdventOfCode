#include "../common.h"

namespace day4a {
	bool is_real_room(const std::string& name, const std::string& checksum) {
		std::array<std::pair<char, char>, 26> letters;
		for(auto c : name) {
			if(c == '-') {
				continue;
			}
			auto& l = letters[c - 'a'];
			l.first = c;
			l.second++;
		}
		std::sort(letters.begin(), letters.end(), [](const auto& a, const auto& b) {
			return a.second > b.second || (a.second == b.second && a.first < b.first);
		});
		for(int i = 0; i < 5; ++i) {
			if(letters[i].first != checksum[i]) {
				return false;
			}
		}
		return true;
	}

	int sum_of_real_rooms(const std::string& input) {
		std::istringstream stream(input);
		std::string line;
		int sum = 0;
		while(stream >> line) {
			std::string name{line.begin(), line.end() - 11};
			std::string checksum{line.end() - 6, line.end() - 1};
			if(is_real_room(name, checksum)) {
				sum += std::stoi(std::string{line.end() - 10, line.end() - 7});
			}
		}
		return sum;
	}

	void run() {
		std::string input = read_file("input/day4.txt");
		std::cout << "day4a ";
		std::cout << sum_of_real_rooms(input) << '\n';
		//std::cout << sum_of_real_rooms("aaaaa-bbb-z-y-x-123[abxyz]\na-b-c-d-e-f-g-h-987[abcde]\nnot-a-real-room-404[oarel]\ntotally-real-room-200[decoy]") << '\n';
	}
}
