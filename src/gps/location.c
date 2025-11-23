#include "gps.h"
#include "sim868_gps.h"
#include "utilities.h"

#include <stdio.h>

static SIM868GPSInfo gpsInfo = {0};

void GPS_NewLocationInfo(ATTerminal* at, char* param)
{
	(void)at; // Unused
	gpsInfo = SIM868_GPS_ParseFixInfo(param);

	printf("Location: %f %f\n", (double)gpsInfo.Latitude, (double)gpsInfo.Longitude);

	GPSInfo info = GPS_GetInfo();
	Observer_Publish(notifier, TOPIC_GPS_UPDATE, &info);
}

GPSInfo GPS_GetInfo()
{
	GPSInfo info;

	info.HasFix    = gpsInfo.FixStatus;
	info.Timestamp = gpsInfo.UTCSeconds;
	info.Altitude  = gpsInfo.Altitude;
	info.Latitude  = gpsInfo.Latitude;
	info.Longitude = gpsInfo.Longitude;
	info.Speed     = gpsInfo.GroundSpeed;
	info.Heading   = gpsInfo.Heading;

	return info;
}
