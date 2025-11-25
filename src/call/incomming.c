#include "call.h"
#include "sim868_call.h"
#include "utilities.h"

void Call_Incoming(ATTerminal* at, char* param)
{
	char* phoneNumber = SIM868_Call_ParseIndentification(param);
	SIM868_Call_Terminate(at);

	Observer_Publish(notifier, TOPIC_CALL_INCOMMING, phoneNumber);
}
