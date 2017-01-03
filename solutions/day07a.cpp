#include "../common.h"

namespace day7a {
	bool is_abba(const char* line) {
		return line[0] != line[1] && line[0] == line[3] && line[1] == line[2];
	}

	int tls_support(const std::string& input) {
		std::istringstream stream(input);
		std::string line;
		int tls = 0;
		while(stream >> line) {
			size_t size = line.size() - 3;
			bool has_tls_support = false;
			for(size_t i = 0; i < size; ++i) {
				if(line[i] == '[') {
					while(line[++i] != ']') {
						if(is_abba(&line[i])) {
							goto nextline;
						}
					}
				} else if(is_abba(&line[i])) {
					has_tls_support = true;
				}
			}
			if(has_tls_support) {
				++tls;
			}
		nextline:;
		}
		return tls;
	}

	void run() {
		std::string input = read_file("input/day7.txt");
		std::cout << "day7a ";
		std::cout << tls_support(input) << '\n';
		//std::cout << tls_support("abba[mnop]qrst") << '\n';
		//std::cout << tls_support("abcd[bddb]xyyx") << '\n';
		//std::cout << tls_support("aaaa[qwer]tyui") << '\n';
		//std::cout << tls_support("ioxxoj[asdfgh]zxcvbn") << '\n';
	}
}