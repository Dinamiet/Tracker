#include "aes.h"
#include "comms.h"
#include "http.h"
#include "sim868_http.h"

static uint8_t KEY[] = {};
static uint8_t IV[] = {};

void HTTP_PostData(char* url, void* data, size_t size)
{
	AES aes;
	AES_Init(&aes, IV, KEY, AES_256);

	size_t encryptedSize = AES_CBC_Encrypt(&aes, data, size, true);

	SIM868_HTTP_Post(atTerm, url, data, encryptedSize);
}
