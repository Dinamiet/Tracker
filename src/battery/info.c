#include "battery.h"
#include "http.h"
#include "sim868_misc.h"

#include <stdio.h>

void Battery_Info(ATTerminal* at, char* param)
{
	(void)at; // Unused

	SIM868MiscBatteryInfo info = SIM868_Misc_ParseBatteryInfo(param);
	printf("Battery: %d %d%% %dV\n", info.Status, info.ChargeLevel, info.Voltage);

	if (info.ChargeLevel < 20 || info.Voltage < 3500)
	{
		char msg[64] = {0};
		sprintf(msg, "%d %d%% %dV", info.Status, info.ChargeLevel, info.Voltage);
		HTTP_PostNotification("Battery", msg);
	}
}
