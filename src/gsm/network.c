#include "gps.h"
#include "gsm.h"
#include "http.h"
#include "sim868_bearer.h"
#include "sim868_gsm.h"

void GSM_EnableNetworkStatusUpdates(ATTerminal* at, bool enable) { SIM868_GSM_NetworkRegistrationStatus(at, enable ? SIM868_GSM_NETWORK_NOTIFY_LOCATION : SIM868_GSM_NETWORK_NOTIFY_NO); }

void GSM_NetworkChange(ATTerminal* at, char* param)
{
	SIM868GSMNetworkInfo info = SIM868_GSM_ParseNetworkInfo(param);

	if (info.Status == SIM868_GSM_NETWORK_STATUS_REGISTERED || info.Status == SIM868_GSM_NETWORK_STATUS_ROAMING)
	{
		if (!GPS_Powered())
			GPS_Enable(true);

		if (!GSM_InternetInitialized())
		{
			GSM_InternetConnect(at);
			HTTP_SetSession(at, true);
		}
	}
}
