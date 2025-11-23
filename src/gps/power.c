#include "gps.h"
#include "sim868_gps.h"

void GPS_PowerChange(ATTerminal* at, char* param)
{
	(void)at; // Unused
	bool powerOn = SIM868_GPS_ParsePowerInfo(param);
}
