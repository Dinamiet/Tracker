#include "gps.h"
#include "gsm.h"
#include "private.h"
#include "sim868_misc.h"

#include <stdio.h>

void Ready_Handler(ATTerminal* at, char* param)
{
	(void)at;    // Unused
	(void)param; // Unused

	SIM868_Misc_CommandEcho(at, false);
	printf("Device Ready\n");

	GSM_ResetState();
	GPS_ResetState();

	if (!GPS_Powered())
		GPS_Enable(true);
}

void Default_Handler(ATTerminal* at, char* param)
{
	(void)at; // Unused

	printf("Unhandled: '%s'\n", param);
}
