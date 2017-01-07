/*
  Christoffer Maliniemi 2016-10-25
  Based pseudocode from wikipedia and RFC 1321 specification.
*/
#include "md5.h"

#include <algorithm>
#include <cstring>

constexpr uint32_t s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

constexpr uint32_t K[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

constexpr uint32_t leftrotate(uint32_t x, uint32_t c) {
	return (x << c) | (x >> (32 - c));
}

constexpr uint32_t bitwise_part(int i, uint32_t x, uint32_t y, uint32_t z) {
	return (i < 16) ? z ^ (x & (y ^ z)) : (i < 32) ? y ^ (z & (x ^ y)) : (i < 48) ? x ^ y ^ z : y ^ (x | ~z);
}

constexpr int data_index(int i) {
	return (i < 16) ? i : (i < 32) ? (5 * i + 1) % 16 : (i < 48) ? (3 * i + 5) % 16 : (7 * i) % 16;
}

template<int index>
constexpr void process(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t* data) {
	a = leftrotate(a + bitwise_part(index, b, c, d) + data[data_index(index)] + K[index], s[index]) + b;
}

MD5Value md5(const char* message, int length) {
	MD5Value value{{0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476}};
	size_t chunks = (length + 8) >> 6;

	int remaining = length;
	bool ending = false;
	for(size_t i = 0; i <= chunks; ++i) {
		uint32_t data[16];
		uint8_t* bufptr = reinterpret_cast<uint8_t*>(data);
		int bytes = std::min(remaining, 64);
		std::memcpy(data, message + remaining - length, bytes);
		std::memset(bufptr + bytes, 0, 64 - bytes);
		if(remaining < 64) {
			if(!ending) {
				*(bufptr + bytes) = 1 << 7;
				ending = true;
			}
			if(i == chunks) {
				*(uint64_t*)(bufptr + 64 - 8) = (length * 8);
			}
		}
		remaining -= bytes;

		uint32_t a = value.chunks.a;
		uint32_t b = value.chunks.b;
		uint32_t c = value.chunks.c;
		uint32_t d = value.chunks.d;

		process< 0>(a, b, c, d, data);
		process< 1>(d, a, b, c, data);
		process< 2>(c, d, a, b, data);
		process< 3>(b, c, d, a, data);
		process< 4>(a, b, c, d, data);
		process< 5>(d, a, b, c, data);
		process< 6>(c, d, a, b, data);
		process< 7>(b, c, d, a, data);
		process< 8>(a, b, c, d, data);
		process< 9>(d, a, b, c, data);
		process<10>(c, d, a, b, data);
		process<11>(b, c, d, a, data);
		process<12>(a, b, c, d, data);
		process<13>(d, a, b, c, data);
		process<14>(c, d, a, b, data);
		process<15>(b, c, d, a, data);
		process<16>(a, b, c, d, data);
		process<17>(d, a, b, c, data);
		process<18>(c, d, a, b, data);
		process<19>(b, c, d, a, data);
		process<20>(a, b, c, d, data);
		process<21>(d, a, b, c, data);
		process<22>(c, d, a, b, data);
		process<23>(b, c, d, a, data);
		process<24>(a, b, c, d, data);
		process<25>(d, a, b, c, data);
		process<26>(c, d, a, b, data);
		process<27>(b, c, d, a, data);
		process<28>(a, b, c, d, data);
		process<29>(d, a, b, c, data);
		process<30>(c, d, a, b, data);
		process<31>(b, c, d, a, data);
		process<32>(a, b, c, d, data);
		process<33>(d, a, b, c, data);
		process<34>(c, d, a, b, data);
		process<35>(b, c, d, a, data);
		process<36>(a, b, c, d, data);
		process<37>(d, a, b, c, data);
		process<38>(c, d, a, b, data);
		process<39>(b, c, d, a, data);
		process<40>(a, b, c, d, data);
		process<41>(d, a, b, c, data);
		process<42>(c, d, a, b, data);
		process<43>(b, c, d, a, data);
		process<44>(a, b, c, d, data);
		process<45>(d, a, b, c, data);
		process<46>(c, d, a, b, data);
		process<47>(b, c, d, a, data);
		process<48>(a, b, c, d, data);
		process<49>(d, a, b, c, data);
		process<50>(c, d, a, b, data);
		process<51>(b, c, d, a, data);
		process<52>(a, b, c, d, data);
		process<53>(d, a, b, c, data);
		process<54>(c, d, a, b, data);
		process<55>(b, c, d, a, data);
		process<56>(a, b, c, d, data);
		process<57>(d, a, b, c, data);
		process<58>(c, d, a, b, data);
		process<59>(b, c, d, a, data);
		process<60>(a, b, c, d, data);
		process<61>(d, a, b, c, data);
		process<62>(c, d, a, b, data);
		process<63>(b, c, d, a, data);
		value.chunks.a += a;
		value.chunks.b += b;
		value.chunks.c += c;
		value.chunks.d += d;
	}
	return value;
}

void uint32_to_chars(uint32_t value, char* buffer) {
	const char* hex_digits = "0123456789abcdef";
	for(int i = 0, j = 1; i < 8; ++i) {
		buffer[i] = hex_digits[((value >> ((i + j) * 4)) & 0xf)];
		j = -j;
	}
}

void md5_to_chars(char* buffer, MD5Value value) {
	uint32_to_chars(value.chunks.a, buffer);
	uint32_to_chars(value.chunks.b, buffer + 8);
	uint32_to_chars(value.chunks.c, buffer + 16);
	uint32_to_chars(value.chunks.d, buffer + 24);
}