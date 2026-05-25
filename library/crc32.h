
#ifndef _CRC32_H_
#define _CRC32_H_

#include <inttypes.h>
#include <stddef.h>

uint32_t crc32b(uint8_t *message, size_t len, uint32_t crc);

#endif
