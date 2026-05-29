
#include "KRAFCOM.h"

#include <string.h>

void KRAFCOM_InitReceiver(KRAFCOM_Receiver *receiver, const uint8_t* key, KRAFCOM_PacketHandler packetHandlerCallback, void *context) {

	if(receiver == NULL) return;
	if(packetHandlerCallback == NULL) return;

	receiver->counter = 0;
	receiver->context = context;
	receiver->packetHandler = packetHandlerCallback;

	receiver->receivedPacket.sop = 0;
	receiver->receivedPacket.type = 0;
	receiver->receivedPacket.crc32 = 0;
	receiver->receivedPacket.time = 0;

	memset(receiver->receivedPacket.iv, 0x00, KRAFCOM_IV_SIZE);
	memset(receiver->receivedPacket.payload, 0x00, KRAFCOM_MAX_PAYLOAD);


}

size_t KRAFCOM_Serialize(uint8_t packetType, const uint8_t* key, void const *payload, size_t payloadSize, uint8_t *destinationBuffer) {

	(void)packetType;
	(void)key;
	(void)payload;
	(void)payloadSize;
	(void)destinationBuffer;
	return 0;

}

void KRAFCOM_Deserialize(KRAFCOM_Receiver *receiver, void const *data, size_t dataLen) {

	(void)receiver;
	(void)data;
	(void)dataLen;

}
