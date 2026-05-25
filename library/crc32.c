
#include "crc32.h"

uint32_t crc32b(uint8_t *message, size_t len, uint32_t crc) {
	uint8_t byte = 0;
	uint32_t mask = 0;

	for(size_t i = 0; i < len; i++) {
		byte = message[i];            // Get next byte.
		crc = crc ^ byte;
		for (uint8_t j = 7; j >= 0; j--) {    // Do eight times.
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
	}
	return ~crc;
}
