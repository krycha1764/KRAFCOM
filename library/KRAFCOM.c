
#include "KRAFCOM.h"
#include "KRAFCOM_USER.h"
#include "tiny-AES-c/aes.h"

#include <string.h>

#define AES256 1
#include "aes.h"

#include "crc32.h"
#include "KRAFCOM_USER.h"

void KRAFCOM_InitReceiver(KRAFCOM_Receiver *receiver, const uint8_t* key, KRAFCOM_PacketHandler packetHandlerCallback, void *context) {

	if(receiver == NULL) return;
	if(packetHandlerCallback == NULL) return;

	receiver->counter = 0;
	receiver->context = context;
	receiver->packetHandler = packetHandlerCallback;

	if(key == NULL) {
		memset(receiver->key, 0x00, KRAFCOM_KEY_SIZE);
	} else {
		memcpy(receiver->key, key, KRAFCOM_KEY_SIZE);
	}

	receiver->receivedPacket.sop = 0;
	receiver->receivedPacket.type = 0;
	receiver->receivedPacket.crc32 = 0;
	receiver->receivedPacket.time = 0;

	memset(receiver->receivedPacket.iv, 0x00, KRAFCOM_IV_SIZE);
	memset(receiver->receivedPacket.payload, 0x00, KRAFCOM_MAX_PAYLOAD);

}

size_t KRAFCOM_Serialize(uint8_t packetType, const uint8_t* key, void const *payload, size_t payloadSize, uint8_t *destinationBuffer) {

	if(destinationBuffer == NULL) return 0;
	if((payload == NULL) && (payloadSize != 0)) return 0;
	if(payloadSize > KRAFCOM_MAX_PAYLOAD) return 0;

	destinationBuffer[0] = KRAFCOM_SOP;
	destinationBuffer[1] = packetType;
	KRAFCOM_getrandom(destinationBuffer + 2, KRAFCOM_IV_SIZE);
	memset(destinationBuffer + 18, 0x00, KRAFCOM_MAX_PAYLOAD);
	memcpy(destinationBuffer + 18, payload, payloadSize);
	destinationBuffer[157] = KRAFCOM_MAX_PAYLOAD - payloadSize;
	uint32_t timetmp = KRAFCOM_gettime();
	memcpy(destinationBuffer + 158, &timetmp, sizeof(timetmp));

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, destinationBuffer + 2);
	AES_CBC_encrypt_buffer(&ctx, destinationBuffer + 18, KRAFCOM_MAX_PAYLOAD + 4);

	uint32_t crc = crc32b(destinationBuffer, KRAFCOM_PACKET_SIZE - 4, KRAFCOM_INIT_CRC);
	memcpy(destinationBuffer + 162, &crc, 4);
	return KRAFCOM_PACKET_SIZE;

}

void KRAFCOM_Deserialize(KRAFCOM_Receiver *receiver, void const *data, size_t dataLen) {

	(void)receiver;
	(void)data;
	(void)dataLen;

}
