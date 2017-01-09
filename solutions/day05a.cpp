#include "../common.h"
#include "../md5.h"

namespace day5a {
	uint32_t byteswap(uint32_t value) {
		return (value & 0xff) << 24 | (value & 0xff00) << 8 | ((value >> 8) & 0xff00) | ((value >> 24) & 0xff);
	}

	uint32_t find_password(const std::string& input) {
		int i = 0;
		size_t size = input.size(), position = 1 << 4 * 7;
		uint32_t password = 0;
		char key[64], *key_end = key + size;
		std::memcpy(key, input.c_str(), size);
		for(;; ++i) {
			_itoa(i, key_end, 10);
			auto hash = byteswap(md5(key, strlen(key)).chunks.a);
			if(hash < 0x00001000) {
				password |= position * ((hash & 0x00000f00) >> 8);
				position >>= 4;
				if(!position) {
					break;
				}
			}
		}
		return password;
	}

	void run() {
		std::cout << "day5a ";
		std::cout << std::hex << find_password("abbhdwsy") << std::dec << '\n';
		//std::cout << std::hex << find_password("abc") << std::dec << '\n';
	}
}
