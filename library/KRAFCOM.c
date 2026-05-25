
#include "KRAFCOM.h"

void KRAFCOM_InitReceiver(KRAFCOM_Receiver *receiver, const uint8_t* key, KRAFCOM_PacketHandler packetHandlerCallback, void *context) {

	(void)receiver;
	(void)key;
	(void)packetHandlerCallback;
	(void)context;

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
