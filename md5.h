#ifndef STIJU_MD5_H
#define STIJU_MD5_H

#include <cstdint>

union MD5Value {
	struct {
		uint32_t a, b, c, d;
	} chunks;
	uint8_t data[16];
};

MD5Value md5(const char* message, int length);
void md5_to_chars(char* buffer, MD5Value value);

#endif
