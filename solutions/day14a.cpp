#include "../common.h"
#include "../md5.h"

namespace day14a {
	uint32_t byteswap(uint32_t value) {
		return (value & 0xff) << 24 | (value & 0xff00) << 8 | ((value >> 8) & 0xff00) | ((value >> 24) & 0xff);
	}
	bool is_sequence(char needle, const char* haystack, int count) {
		for(int i = 1; i < count; ++i) {
			if(haystack[i] != needle) {
				return false;
			}
		}
		return true;
	}
	char find_sequence(const char* haystack, char needle, int count) {
		for(int i = 0; i < 33 - count; ++i) {
			if((needle == 0 || haystack[i] == needle) && is_sequence(haystack[i], haystack + i, count)) {
				return haystack[i];
			}
		}
		return 0;
	}
	struct MD5Cache {
		int index;
		char md5[36];
	};
	auto hash_and_stretch(const char *key, int stretch) {
		auto hash = md5(key, strlen(key));
		hash.chunks.a = byteswap(hash.chunks.a);
		hash.chunks.b = byteswap(hash.chunks.b);
		hash.chunks.c = byteswap(hash.chunks.c);
		hash.chunks.d = byteswap(hash.chunks.d);
		for(int i = 0; i < stretch; ++i) {
			char buffer[36];
			std::snprintf(buffer, 36, "%.8x%.8x%.8x%.8x", hash.chunks.a, hash.chunks.b, hash.chunks.c, hash.chunks.d);
			hash = md5(buffer, 32);
			hash.chunks.a = byteswap(hash.chunks.a);
			hash.chunks.b = byteswap(hash.chunks.b);
			hash.chunks.c = byteswap(hash.chunks.c);
			hash.chunks.d = byteswap(hash.chunks.d);
		}
		return hash;
	}

	uint32_t get_index(const std::string& input, int stretch) {
		size_t size = input.size();
		char key[64], *key_end = key + size;
		std::memcpy(key, input.c_str(), size);
		size = sizeof(key) - size;
		std::array<MD5Cache, 1000> hash_cache;
		std::memset(hash_cache.data(), 0, sizeof(hash_cache));
		hash_cache[0].index = -1;
		for(int i = 0, found = 0;; ++i) {
			auto& hc = hash_cache[i % 1000];
			if(hc.index != i) {
				hc.index = i;
				std::snprintf(key_end, size, "%d", i);
				auto hash = hash_and_stretch(key, stretch);
				std::snprintf(hc.md5, 36, "%.8x%.8x%.8x%.8x", hash.chunks.a, hash.chunks.b, hash.chunks.c, hash.chunks.d);
			}
			char c = find_sequence(hc.md5, 0, 3);
			if(c != 0) {
				for(int j = i + 1; j <= i + 1000; ++j) {
					auto& hc = hash_cache[j % 1000];
					if(hc.index != j) {
						hc.index = j;
						std::snprintf(key_end, size, "%d", j);
						auto hash = hash_and_stretch(key, stretch);
						std::snprintf(hc.md5, 36, "%.8x%.8x%.8x%.8x", hash.chunks.a, hash.chunks.b, hash.chunks.c, hash.chunks.d);
					}
					if(find_sequence(hc.md5, c, 5)) {
						if(++found == 64) {
							return i;
						}
						break;
					}
				}
				
			}
		}
		return 0;
	}
	
	void run() {
		std::cout << "day14a " << get_index("ahsbgdzn", 0) << '\n';
		std::cout << "day14b " << get_index("ahsbgdzn", 2016) << '\n';
		//std::cout << "day14a " << get_index("abc", 0) << '\n';
		//std::cout << "day14a " << get_index("abc", 2016) << '\n';
	}
}
