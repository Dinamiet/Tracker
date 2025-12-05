#include "comms.h"
#include "config.h"
#include "math.h"
#include "http.h"
#include "private.h"
#include "sim868_http.h"
#include "utilities.h"

static bool     ongoingRequest   = false;
static uint32_t requestStartTime = 0;

bool HTTP_IsBusy()
{
	if (ongoingRequest)
	{
		uint32_t       now     = Time_ms();
		const uint32_t timeout = (CONFIG_HTTP_BUSY_TIMEOUT + 1) * 1000; // Extra second to allow timeout
		if ((requestStartTime + timeout) < now)
		{
			HTTP_SetSession(atTerm, false);
			HTTP_SetSession(atTerm, true);
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
