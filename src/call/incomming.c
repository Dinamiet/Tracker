#include "call.h"
#include "sim868_call.h"

void Call_Incoming(ATTerminal* at, char* param)
{
	(void)at; // Unused
	char* phoneNumber = SIM868_Call_ParseIndentification(param);
}
