#include "http.h"
#include "sim868_http.h"

void HTTP_RequestDone(ATTerminal* at, char* param)
{
	(void)at; // Unused
	SIM868HTTPActionInfo response = SIM868_HTTP_ParseActionInfo(param);
}
