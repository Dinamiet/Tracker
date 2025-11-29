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

static void movement_Handler(const void* data)
{
	const GPSInfo* info = data;

	if (info->Speed > CONFIG_STATIONARY_SPEED_THRESHOLD)
	{
		if (stationary)
		{
			printf("Moving\n");
			HTTP_PostNotification("Movement", "Moving");
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
				HTTP_PostNotification("Movement", "Stopped");
				stationary = true;
			}
		}
	}
}

static void gpsData_Handler(const void* data)
{
	const GPSInfo* info = data;

	if (!info->HasFix)
		return;

	printf("Location: %f %f %f\n", info->Latitude, info->Longitude, info->Speed);

	if (stationary)
		return;

	HTTP_PostLocation(info);
}

static void callIncomming_Handler(const void* data)
{
	const char* number = data;
	printf("Call from %s\n", number);
	HTTP_PostNotification("Call", number);
}

static void smsReceive_Handler(const void* data)
{
	const SMSMessage* sms = data;
	printf("SMS from %s: '%s'\n", sms->Sender, sms->Message);
	HTTP_PostNotification(sms->Sender, sms->Message);
}

void Tracking_Setup()
{
	Observer_Subscribe(notifier, &movementSubcription, TOPIC_GPS_UPDATE, movement_Handler);
	Observer_Subscribe(notifier, &gpsDataSubcription, TOPIC_GPS_UPDATE, gpsData_Handler);
	Observer_Subscribe(notifier, &callIncommingSubscription, TOPIC_CALL_INCOMMING, callIncomming_Handler);
	Observer_Subscribe(notifier, &smsReceivedSubscription, TOPIC_SMS_RECEIVED, smsReceive_Handler);
}
