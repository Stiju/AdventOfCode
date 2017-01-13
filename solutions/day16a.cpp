#include "../common.h"

namespace day16a {
	std::string almost_dragon_curve(std::string data, int size) {
		int len = data.size();
		data.resize(size);
		for(;;) {
			int max_size = size - len - 1;
			if(max_size < 0) {
				break;
			}
			data[len] = '0';
			int iterations = std::min(len, max_size);
			for(int i = 0; i < iterations; ++i) {
				data[len + i + 1] = data[len - i - 1] == '0' ? '1' : '0';
			}
			len = len * 2 + 1;
		}
		return data;
	}

	std::string calculate_checksum(const std::string& data) {
		std::string checksum;
		int len = data.size() / 2;
		checksum.resize(len);
		for(int i = 0; i < len; ++i) {
			int x = i * 2;
			checksum[i] = data[x] == data[x + 1] ? '1' : '0';
		}
		return checksum;
	}

	std::string dragon_checksum(const std::string& input, int disk_size) {
		auto checksum = almost_dragon_curve(input, disk_size);
		do {
			checksum = calculate_checksum(checksum);
		} while(!(checksum.size() & 1));
		return checksum;
	}

	void run() {
		std::cout << "day15a " << dragon_checksum("10011111011011001", 272) << "\n";
		std::cout << "day15b " << dragon_checksum("10011111011011001", 35651584) << '\n';
	}
}