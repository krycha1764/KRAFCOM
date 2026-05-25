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
 * 	CRC		(4B)	- CRC32 checksum, little endian, calculated from all previous fields (after encryption)
 */

#define KRAFCOM_IV_SIZE 16
#define KRAFCOM_KEY_SIZE 16
#define KRAFCOM_MAX_PAYLOAD 140
#define KRAFCOM_PACKET_SIZE 166

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KRAFCOM_PACKED __attribute__((packed))

typedef struct KRAFCOM_PACKED {
	uint8_t sop;
	uint8_t type;
	uint8_t iv[KRAFCOM_IV_SIZE];
	uint8_t payload[KRAFCOM_MAX_PAYLOAD];
	uint32_t time;
	uint32_t crc32;
} KRAFCOM_Packet;

/**
 * Type describing a callback function that will be called when a packet is received.
 *
 * @param packet packet that is received
 * @param userContext user defined context associated with the protocol receiver instance
 */
typedef void (*KRAFCOM_PacketHandler)(const KRAFCOM_Packet* packet, void *userContext);

typedef struct {
	KRAFCOM_Packet receivedPacket;
	size_t counter;
	KRAFCOM_PacketHandler packetHandler;
	void* context;
} KRAFCOM_Receiver;



/**
 * @brief Initializes the KRAFCOM packet receiver.
 *
 * @param receiver pointer to the KRAFCOM receiver structure
 * @param key key used for decryption, must be 16 bytes long
 * @param packetHandlerCallback callback function that will be called each time a packet is received
 * @param context general purpose context, that will be fed back to the callback function
 */
void KRAFCOM_InitReceiver(KRAFCOM_Receiver *receiver, const uint8_t* key, KRAFCOM_PacketHandler packetHandlerCallback, void *context);

/**
 * @brief Serializes the packet
 *
 * in the destination buffer as an array of bytes. The number of bytes written to the destination buffer
 * (length of the whole packet) shall be returned. In case of error, this function shall return 0.
 * @param packetType type of packet
 * @param key key used for encryption, must be 16 bytes long
 * @param payload pointer to the payload data or NULL if the packet has no payload
 * @param payloadSize number of bytes in the payload or 0 if the packet has no payload
 * @param destinationBuffer place to store the packet bytes (must be large enough!)
 *
 * @return number of bytes written to the destinationBuffer or 0 in case of error
 *
 */
size_t KRAFCOM_Serialize(uint8_t packetType, const uint8_t* key, void const *payload, size_t payloadSize, uint8_t *destinationBuffer);

/**
 * @brief Deserializes the chunk of data, searching for valid KRAFCOM packets
 *
 * This function is supposed to be fed with an incoming stream of data and it's job is to try to find a valid
 * KRAFCOM packet in this stream.
 * If a valid packet is found and buffered, this function shall call the packetHandlerCallback.
 * @param receiver pointer to the KRAFCOM receiver structure
 * @param data incoming data
 * @param dataLen number of bytes in the incoming data
 */
void KRAFCOM_Deserialize(KRAFCOM_Receiver *receiver, void const *data, size_t dataLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
