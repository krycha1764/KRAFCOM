#ifndef _KRAFCOM_USER_H_
#define _KRAFCOM_USER_H_

#include <stddef.h>
#include <time.h>

/**
 * @brief get random bytes
 *
 * @param buf buffer to be filled with random data
 * @param len number of bytes to be written
 *
 * @return number of written bytes
 */
size_t KRAFCOM_getrandom(const void* buff, size_t len);

/**
 * @brief get current time
 *
 * @return current time in seconds
 */
time_t KRAFCOM_gettime();


#endif
