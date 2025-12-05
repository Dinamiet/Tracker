#include "config.h"
#include "http.h"
#include "sim868_http.h"

void HTTP_SetSession(ATTerminal* at, bool open)
{
	if (open)
		SIM868_HTTP_StartSession(at, CONFIG_CONNECTION_ID, CONFIG_HTTP_BUSY_TIMEOUT);
	else
		SIM868_HTTP_TerminateSession(at);
}
