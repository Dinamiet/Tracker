#include "aes.h"
#include "comms.h"
#include "http.h"
#include "private.h"
#include "sim868_http.h"
#include "secrets.h"

void HTTP_PostData(char* url, void* data, size_t size)
{
	if (HTTP_IsBusy())
		return;

	AES aes;
	AES_Init(&aes, IV, KEY, AES_256);

	size_t encryptedSize = AES_CBC_Encrypt(&aes, data, size, true);

	HTTP_SetBusy(true);
	SIM868_HTTP_Post(atTerm, url, data, encryptedSize);
}
