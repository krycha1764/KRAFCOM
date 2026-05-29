
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <sys/random.h>
#include <time.h>

#include "KRAFCOM.h"

size_t KRAFCOM_getrandom(void* buff, size_t len) {
	return getrandom(buff, len, 0);
}

time_t KRAFCOM_gettime() {
	return time(NULL);
}

void pack_ready(const KRAFCOM_Packet* packet, void *userContext) {
	printf("DECODED:\n");
	printf("\tTYPE: %d\n", packet->type);
	printf("\tDATA: %s\n", packet->payload);
}

int main() {
	uint8_t data[140] = {0};
	uint8_t key[32] = {0};
	uint8_t frame[512] = {0};

	getrandom(key, 32, 0);
	size_t datalen = sprintf((char*)data, "Hello");

	printf("BEFORE ENCRYPTION:\n");
	printf("\tDATA: %s\n", (char*)data);

	size_t len = 0;

	for(int n = 0; n < 2; n++) {
		len = KRAFCOM_Serialize(0, key, data, datalen+1, frame);
		printf("FRAME %d:\n\t", n);
		for(size_t i = 0; i < len; i++) {
			printf("%02hhX", frame[i]);
		}
		printf("\n");
	}

	KRAFCOM_Receiver receive;

	KRAFCOM_InitReceiver(&receive, key, pack_ready, NULL);
	KRAFCOM_Deserialize(&receive, frame, len);


	printf("\nEND\n");

	return 0;
}
