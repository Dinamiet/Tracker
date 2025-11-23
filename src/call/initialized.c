#include "call.h"
#include "gsm.h"
#include "sim868_call.h"

void Call_Initialized(ATTerminal* at, char* param)
{
	(void)at;
	(void)param;
	GSM_EnableNetworkStatusUpdates(at, true);
}
