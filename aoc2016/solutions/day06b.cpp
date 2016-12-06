#include "../common.h"

namespace day6b {
	std::string recover_message(const std::string& input) {
		std::istringstream stream(input);
		std::string line;
		stream >> line;
		std::string ret(line.size(), ' ');
		std::vector<std::array<std::pair<char, char>, 26>> columns(line.size());
		do {
			int i = 0;
			for(auto c : line) {
				auto& l = columns[i++][c - 'a'];
				l.first = c;
				l.second++;
			}
		} while(stream >> line);

		int i = 0;
		for(auto& letters : columns) {
			std::sort(letters.begin(), letters.end(), [](const auto& a, const auto& b) {
				if(a.second == 0) return false;
				if(b.second == 0) return true;
				return a.second < b.second;
			});
			ret[i++] = letters[0].first;
		}
		return ret;
	}

	void run() {
		std::string input = read_file("input/day6.txt");
		std::cout << "day6b ";
		std::cout << recover_message(input) << '\n';
		//std::cout << recover_message("eedadn\ndrvtee\neandsr\nraavrd\n"
		//	"atevrs\ntsrnev\nsdttsa\nrasrtv\n"
		//	"nssdts\nntnada\nsvetve\ntesnvt\n"
		//	"vntsnd\nvrdear\ndvrsen\nenarar") << '\n';
	}
}