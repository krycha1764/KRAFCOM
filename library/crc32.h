
#ifndef _CRC32_H_
#define _CRC32_H_

#include <inttypes.h>
#include <stddef.h>


/**
 * @brief calculated crc32 from given data
 *
 * @param data pointer to data
 * @param len length of data
 * @param crc initial crc, used if calculating crc from multiple chunks of data
 */
uint32_t crc32b(const uint8_t *data, const size_t len, uint32_t crc);

#endif
