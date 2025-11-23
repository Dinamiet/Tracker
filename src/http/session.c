#include "http.h"
#include "sim868_http.h"

void HTTP_SetSession(ATTerminal* at, bool open)
{
	if (open)
		SIM868_HTTP_StartSession(at, 1);
	else
		SIM868_HTTP_TerminateSession(at);
}
