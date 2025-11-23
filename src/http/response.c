#include "http.h"
#include "private.h"
#include "sim868_http.h"

#include <stdio.h>

void HTTP_RequestDone(ATTerminal* at, char* param)
{
	(void)at; // Unused
	SIM868HTTPActionInfo response = SIM868_HTTP_ParseActionInfo(param);

	HTTP_SetBusy(false);

	printf("HTTP request status: %d\n", response.Status);
}
