#include "../common.h"
#include "../md5.h"

namespace day14a {
	uint32_t byteswap(uint32_t value) {
		return (value & 0xff) << 24 | (value & 0xff00) << 8 | ((value >> 8) & 0xff00) | ((value >> 24) & 0xff);
	}
	bool is_sequence(const char* haystack, char needle, int count) {
		for(int i = 1; i < count; ++i) {
			if(haystack[i] != needle) {
				return false;
			}
		}
		return true;
	}
	char find_sequence(const char* haystack, char needle, int count) {
		for(int i = 0; i < 33 - count; ++i) {
			if((needle == 0 || haystack[i] == needle) && is_sequence(haystack + i, haystack[i], count)) {
				return haystack[i];
			}
		}
		return 0;
	}
	struct MD5Cache {
		int index;
		char md5[36];
	};
	void hash_and_stretch(const char *key, int index, int stretch, MD5Cache& cache) {
		int length = std::snprintf(cache.md5, 36, "%s%d", key, index);
		for(int i = 0; i <= stretch; ++i) {
			auto hash = md5(cache.md5, length);
			hash.chunks.a = byteswap(hash.chunks.a);
			hash.chunks.b = byteswap(hash.chunks.b);
			hash.chunks.c = byteswap(hash.chunks.c);
			hash.chunks.d = byteswap(hash.chunks.d);
			length = std::snprintf(cache.md5, 36, "%.8x%.8x%.8x%.8x", hash.chunks.a, hash.chunks.b, hash.chunks.c, hash.chunks.d);
		}
		cache.index = index;
	}

	uint32_t get_index(const std::string& input, int stretch) {
		const char* key = input.c_str();
		std::vector<MD5Cache> hash_cache(1000);
		hash_cache[0].index = -1;
		for(int i = 0, found = 0;; ++i) {
			auto& hc = hash_cache[i % 1000];
			if(hc.index != i) {
				hash_and_stretch(key, i, stretch, hc);
			}
			char c = find_sequence(hc.md5, 0, 3);
			if(c != 0) {
				for(int j = i + 1; j <= i + 1000; ++j) {
					auto& hc = hash_cache[j % 1000];
					if(hc.index != j) {
						hash_and_stretch(key, j, stretch, hc);
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
