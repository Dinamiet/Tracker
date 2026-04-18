#include "tracking.h"

#include "battery.h"
#include "call.h"
#include "comms.h"
#include "config.h"
#include "gps.h"
#include "http.h"
#include "sms.h"
#include "tasks.h"
#include "utilities.h"

#include <stdio.h>

static ObserverSubscription movementSubcription;
static ObserverSubscription gpsDataSubcription;
static ObserverSubscription callIncommingSubscription;
static ObserverSubscription smsReceivedSubscription;
static SchedulerTask        forceUpdateTask;

static bool     stationary          = false;
static bool     forceLocationUpdate = false;
static uint32_t stationaryStartTime = 0;

static void movement_Handler(const void* data);
static void gpsData_Handler(const void* data);
static void forceUpdate_Handler(void* _);
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

	if (stationary && !forceLocationUpdate)
		return;

	HTTP_PostLocation(info);
	forceLocationUpdate = false;
}

static void forceUpdate_Handler(void* _)
{
	(void)_; // Unused
	forceLocationUpdate = true;
}

static void callIncomming_Handler(const void* data)
{
	const char* number = data;
	printf("Call from %s\n", number);
	HTTP_PostNotification("Call", number);
	GPSInfo info = GPS_GetInfo();
	while (HTTP_IsBusy()) { Comms_Process(); }
	printf("Sending Location\n");
	HTTP_PostLocation(&info);
	printf("Requesting Battery info\n");
	Battery_RequestInfo();
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

	Scheduler_CreateRecurringTask(scheduler, &forceUpdateTask, TASK_FORCE_LOCATION_UPDATE, forceUpdate_Handler, NULL, CONFIG_FORCE_LOCATION_UPDATE_INTERVAL);
}
