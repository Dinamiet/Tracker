#include "http.h"
#include "sim868_http.h"

#include <stdio.h>

static bool haveOngoingRequest = false;

void HTTP_RequestDone(ATTerminal* at, char* param)
{
	(void)at; // Unused
	SIM868HTTPActionInfo response = SIM868_HTTP_ParseActionInfo(param);
	haveOngoingRequest            = false;

	printf("HTTP request status: %d\n", response.Status);
}
