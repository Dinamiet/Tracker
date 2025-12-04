#include "comms.h"
#include "config.h"
#include "math.h"
#include "private.h"
#include "sim868_http.h"
#include "utilities.h"

static bool     ongoingRequest   = false;
static uint32_t requestStartTime = 0;

bool HTTP_IsBusy()
{
	if (ongoingRequest)
	{
		uint32_t now = Time_ms();
		if ((requestStartTime + CONFIG_HTTP_BUSY_TIMEOUT) < now)
		{
			SIM868_HTTP_TerminateSession(atTerm);
			SIM868_HTTP_StartSession(atTerm, CONFIG_CONNECTION_ID);
			ongoingRequest = false;
		}
	}

	return ongoingRequest;
}

void HTTP_SetBusy(bool busy)
{
	if (busy)
		requestStartTime = Time_ms();

	ongoingRequest = busy;
}
