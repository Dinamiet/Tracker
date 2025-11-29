#include "aes.h"
#include "comms.h"
#include "config.h"
#include "gsm.h"
#include "http.h"
#include "private.h"
#include "secrets.h"
#include "sim868_http.h"

#include <stdio.h>

void HTTP_PostNotification(const char* title, const char* message)
{
	char  payload[128];
	char* url = CONFIG_NOTIFY_POST_URL CONFIG_DEVICE_NAME;

	size_t size = sprintf(payload, "{\"title\":\"%s\",\"body\":\"%s\"}", title, message);

	while (HTTP_IsBusy()) { Comms_Process(); }

	AES aes;
	AES_Init(&aes, IV, SERVER_KEY, AES_256);

	size_t encryptedSize = AES_CBC_Encrypt(&aes, payload, size, true);

	if (GSM_InternetInitialized())
	{
		HTTP_SetBusy(true);
		SIM868_HTTP_Post(atTerm, url, payload, encryptedSize);
	}
}

void HTTP_PostLocation(const GPSInfo* info)
{
	if (HTTP_IsBusy())
		return;

	char  payload[128];
	char* url = CONFIG_LOCATION_POST_URL CONFIG_DEVICE_NAME;

	size_t size = sprintf(payload, "{\"time\":%ld,\"lat\":%f,\"lng\":%f}", info->Timestamp, info->Latitude, info->Longitude);

	AES aes;
	AES_Init(&aes, IV, CLIENT_KEY, AES_256);

	size_t encryptedSize = AES_CBC_Encrypt(&aes, payload, size, true);

	if (GSM_InternetInitialized())
	{
		HTTP_SetBusy(true);
		SIM868_HTTP_Post(atTerm, url, payload, encryptedSize);
	}
}
