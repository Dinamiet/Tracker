#include "call.h"
#include "sim868_call.h"

#include <stdio.h>

void Call_Incoming(ATTerminal* at, char* param)
{
	char* phoneNumber = SIM868_Call_ParseIndentification(param);
	printf("Incomming call from: '%s'\n", phoneNumber);
	SIM868_Call_Terminate(at);
}
