#ifndef _KRAFCOM_H_
#define _KRAFCOM_H_

/*
 * packet structure:
 * 	SOP		(1B)	- start of packet, always 0xAB
 * 	TYPE 	(1B)	- type of packet, 0x00 - 0xFF
 * 	IV		(16B)	- initialization vector for AES
 * 	AES encrypted (AES-256 CBC)
 * 		PAYLOAD		(140B)	- packet payload, PKCS7 padded
 * 		TIME		(4B)	-unix timestamp. little endian
 * 	CRC		(4B)	- CRC32 checksum, little endian
 */

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
} // extern "C"
#endif

#endif
