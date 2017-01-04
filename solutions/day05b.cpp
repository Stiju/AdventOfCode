#include "../common.h"
#include "../md5.h"

namespace day5b {
	uint32_t byteswap(uint32_t value) {
		return (value & 0xff) << 24 | (value & 0xff00) << 8 | ((value >> 8) & 0xff00) | ((value >> 24) & 0xff);
	}

	uint32_t find_password(const std::string& input) {
		int i = 0, j = 0;
		size_t size = input.size();
		uint32_t password = 0;
		char key[64], *key_end = key + size, bitset = 0;
		std::memcpy(key, input.c_str(), size);
		size = sizeof(key) - size;
		for(;; ++i) {
			std::snprintf(key_end, size, "%d", i);
			auto hash = byteswap(md5(key, strlen(key)).chunks.a);
			if(hash < 0x00001000) {
				size_t position = ((hash & 0x00000f00) >> 8);
				if(position >= 8) {
					continue;
				}
				if(((bitset >> position) & 1) == 1) {
					continue;
				}
				bitset |= 1 << position;
				position = 1 << 4 * (7u - position);
				password |= position * ((hash & 0x000000f0) >> 4);

				if(++j == 8) {
					break;
				}
			}
		}
		return password;
	}

	void run() {
		std::cout << "day5b ";
		std::cout << std::hex << find_password("abbhdwsy") << std::dec << '\n';
		//std::cout << std::hex << find_password("abc") << std::dec << '\n';
	}
}
