#include "../common.h"

namespace day15a {
	struct Disc {
		int position, max;
	};

	std::istream& operator >> (std::istream& is, Disc& disc) {
		std::string d;
		return is >> d >> d >> d >> disc.max >> d >> d >> d >> d >> d >> d >> d >> disc.position >> d;
	}

	auto get_discs(const std::string& input) {
		std::vector<Disc> discs;
		std::istringstream stream(input);
		Disc disc;
		while(stream >> disc) {
			discs.emplace_back(disc);
		}
		return discs;
	}

	int bruteforce_start_time(const std::vector<Disc>& discs) {
		int disc_count = discs.size();
		for(int time = 0;; ++time) {
			bool exit = true;
			for(int i = 0; i < disc_count; ++i) {
				auto& disc = discs[i];
				if((disc.position + time + i + 1) % disc.max) {
					exit = false;
					break;
				}
			}
			if(exit) {
				return time;
			}
		}
		return 0;
	}

	auto get_start_time(const std::string& input) {
		auto discs = get_discs(input);
		int a = bruteforce_start_time(discs);
		discs.emplace_back(Disc{0, 11});
		int b = bruteforce_start_time(discs);
		return std::make_pair(a, b);
	}

	void run() {
		std::string input = read_file("input/day15.txt");
		auto result = get_start_time(input);
		std::cout << "day15a " << result.first << "\nday15b " << result.second << '\n';
	}
}