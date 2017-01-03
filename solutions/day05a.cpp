#include "../common.h"
#include "../md5.h"

namespace day5a {
	uint32_t byteswap(uint32_t value) {
		return (value & 0xff) << 24 | (value & 0xff00) << 8 | (value >> 8) & 0xff00 | (value >> 24) & 0xff;
	}

	uint32_t find_password(const std::string& input) {
		size_t i = 0, size = input.size(), position = 1 << 4 * 7;
		uint32_t password = 0;
		char key[64], *key_end = key + size;
		std::memcpy(key, input.c_str(), size);
		size = sizeof(key) - size;
		for(;; ++i) {
			std::snprintf(key_end, size, "%d", i);
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
		std::cout << (void*)find_password("abbhdwsy") << '\n';
		//std::cout << (void*)find_password("abc") << '\n';
	}
}