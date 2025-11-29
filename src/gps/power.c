#include "comms.h"
#include "config.h"
#include "gps.h"
#include "sim868_gps.h"

static bool powerOn = false;

void GPS_ResetState() { powerOn = false; }

void GPS_Enable(bool enable) { SIM868_GPS_Power(atTerm, enable, CONFIG_GPS_FIX_INTERVAL); }

void GPS_PowerChange(ATTerminal* at, char* param)
{
	(void)at; // Unused
	powerOn = SIM868_GPS_ParsePowerInfo(param);
}

bool GPS_Powered() { return powerOn; }
