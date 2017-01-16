#include "../common.h"

namespace day16a {
	void almost_dragon_curve(std::string& data, int size) {
		int len = data.size();
		data.resize(size);
		char* ptr = const_cast<char*>(data.data());
		for(;;) {
			int iterations = std::min(len, size - len - 1);
			if(iterations < 0) {
				break;
			}
			ptr[len] = '0';
			for(int i = 0; i < iterations; ++i) {
				ptr[len + i + 1] = ptr[len - i - 1] == '0' ? '1' : '0';
			}
			len = len * 2 + 1;
		}
	}

	void calculate_checksum(std::string& data) {
		int len = data.size();
		char* ptr = const_cast<char*>(data.data());
		do {
			len /= 2;
			for(int i = 0; i < len; ++i) {
				int x = i * 2;
				ptr[i] = ptr[x] == ptr[x + 1] ? '1' : '0';
			}
		} while(!(len & 1));
		data.resize(len);
	}

	std::string dragon_checksum(std::string checksum, int disk_size) {
		almost_dragon_curve(checksum, disk_size);
		calculate_checksum(checksum);
		return checksum;
	}

	void run() {
		std::cout << "day16a " << dragon_checksum("10011111011011001", 272) << "\n";
		std::cout << "day16b " << dragon_checksum("10011111011011001", 35651584) << '\n';
	}
}