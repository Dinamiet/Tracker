#include "gps.h"
#include "sim868_gps.h"

void GPS_NewLocationInfo(ATTerminal* at, char* param)
{
	(void)at; // Unused
	SIM868GPSInfo info = SIM868_GPS_ParseFixInfo(param);
}
