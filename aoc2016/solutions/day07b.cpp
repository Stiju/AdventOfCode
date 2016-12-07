#include "../common.h"

namespace day7b {
	bool is_aba(const char* line) {
		return line[0] != line[1] && line[0] == line[2];
	}
	bool is_bab(const char* line, const char* aba) {
		return line[0] == aba[1] && line[1] == aba[0] && line[2] == aba[1];
	}

	auto find_hypernets(const std::string& line) {
		std::vector<const char*> ret;
		for(size_t i = 0; i < line.size(); ++i) {
			if(line[i] == '[') {
				ret.emplace_back(&line[i + 1]);
			}
		}
		return ret;
	}

	int ssl_support(const std::string& input) {
		std::istringstream stream(input);
		std::string line;
		int ssl = 0;
		while(stream >> line) {
			auto hypernets = find_hypernets(line);
			size_t size = line.size() - 2;
			for(size_t i = 0; i < size; ++i) {
				if(line[i] == '[') {
					while(line[++i] != ']');
				} else if(is_aba(&line[i])) {
					for(auto p : hypernets) {
						for(; *p != ']'; ++p) {
							if(is_bab(p, &line[i])) {
								++ssl;
								goto nextline;
							}
						}
					}
				}
			}
		nextline:;
		}
		return ssl;
	}

	void run() {
		std::string input = read_file("input/day7.txt");
		std::cout << "day7b ";
		std::cout << ssl_support(input) << '\n';
		//std::cout << ssl_support("aba[bab]xyz") << '\n';
		//std::cout << ssl_support("xyx[xyx]xyx") << '\n';
		//std::cout << ssl_support("aaa[kek]eke") << '\n';
		//std::cout << ssl_support("zazbz[bzb]cdb") << '\n';
	}
}