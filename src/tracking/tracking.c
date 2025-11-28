#include "tracking.h"

#include "call.h"
#include "comms.h"
#include "config.h"
#include "gps.h"
#include "http.h"
#include "sms.h"
#include "utilities.h"

#include <stdio.h>

static ObserverSubscription movementSubcription;
static ObserverSubscription gpsDataSubcription;
static ObserverSubscription callIncommingSubscription;
static ObserverSubscription smsReceivedSubscription;

static bool     stationary          = false;
static uint32_t stationaryStartTime = 0;

static void movement_Handler(const void* data);
static void gpsData_Handler(const void* data);
static void callIncomming_Handler(const void* data);
static void smsReceive_Handler(const void* data);

static void sendNotification(const char* title, const char* message);

static void movement_Handler(const void* data)
{
	const GPSInfo* info = data;
	if (!info->HasFix)
		return;

	if (info->Speed > CONFIG_STATIONARY_SPEED_THRESHOLD)
	{
		if (stationary)
		{
			printf("Moving\n");
			sendNotification("Movement", "Moving");
		}
		stationary          = false;
		stationaryStartTime = info->Timestamp;
	}
	else
	{
		if (!stationary)
		{
			if (info->Timestamp - stationaryStartTime > CONFIG_STATIONARY_TIMEOUT)
			{
				printf("Stopped\n");
				sendNotification("Movement", "Stopped");
				stationary = true;
			}
		}
	}
}

static void gpsData_Handler(const void* data)
{
	const GPSInfo* info = data;
	char           payload[128];
	char* url = CONFIG_LOCATION_POST_URL CONFIG_DEVICE_NAME;

	printf("Location: %f %f\n", (double)info->Latitude, (double)info->Longitude);

	size_t size = sprintf(payload, "{\"time\":%ld,\"lat\":%f,\"lng\":%f}", info->Timestamp, info->Latitude, info->Longitude);

	HTTP_PostSecretData(url, payload, size);
}

static void callIncomming_Handler(const void* data)
{
	const char* number = data;
	printf("Call from %s\n", number);
	sendNotification("Call", number);
}

static void smsReceive_Handler(const void* data)
{
	const SMSMessage* sms = data;
	printf("SMS from %s: '%s'\n", sms->Sender, sms->Message);
	sendNotification(sms->Sender, sms->Message);
}

static void sendNotification(const char* title, const char* message)
{
	char  payload[128];
	char* url = CONFIG_NOTIFY_POST_URL CONFIG_DEVICE_NAME;

	size_t size = sprintf(payload, "{\"title\":\"%s\",\"body\":\"%s\"}", title, message);

	while (HTTP_IsBusy()) { Comms_Process(); }

	HTTP_PostData(url, payload, size);
}

void Tracking_Setup()
{
	Observer_Subscribe(notifier, &movementSubcription, TOPIC_GPS_UPDATE, movement_Handler);
	Observer_Subscribe(notifier, &gpsDataSubcription, TOPIC_GPS_UPDATE, gpsData_Handler);
	Observer_Subscribe(notifier, &callIncommingSubscription, TOPIC_CALL_INCOMMING, callIncomming_Handler);
	Observer_Subscribe(notifier, &smsReceivedSubscription, TOPIC_SMS_RECEIVED, smsReceive_Handler);
}
