#include "../common.h"
#include "../md5.h"

namespace day14a {
	template<int N>
	constexpr bool is_sequence(const char* haystack, char needle) {
		return needle == haystack[N - 1] && is_sequence<N - 1>(haystack, needle);
	}
	template<>
	constexpr bool is_sequence<1>(const char* haystack, char needle) {
		return needle == haystack[0];
	}
	template<int count>
	char find_sequence(const char* haystack, char needle) {
		for(int i = 0; i < 33 - count; ++i) {
			if((!needle || haystack[i] == needle) && is_sequence<count>(haystack + i, haystack[i])) {
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
			md5_to_chars(cache.md5, hash);
			length = 32;
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
			char c = find_sequence<3>(hc.md5, 0);
			if(c != 0) {
				for(int j = i + 1; j <= i + 1000; ++j) {
					auto& hc = hash_cache[j % 1000];
					if(hc.index != j) {
						hash_and_stretch(key, j, stretch, hc);
					}
					if(find_sequence<5>(hc.md5, c)) {
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
