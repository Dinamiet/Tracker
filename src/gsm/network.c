#include "gsm.h"
#include "sim868_gsm.h"

void GSM_NetworkChange(ATTerminal* at, char* param)
{
	(void)at; // Unused
	SIM868GSMNetworkInfo info = SIM868_GSM_ParseNetworkInfo(param);
}
