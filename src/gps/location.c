#include "gps.h"
#include "sim868_gps.h"

static SIM868GPSInfo gpsInfo = {0};

void GPS_NewLocationInfo(ATTerminal* at, char* param)
{
	(void)at; // Unused
	gpsInfo = SIM868_GPS_ParseFixInfo(param);
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
