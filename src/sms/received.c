#include "sim868_sms.h"
#include "sms.h"
#include "utilities.h"

void SMS_ReceivedNewMsg(ATTerminal* at, char* param)
{
	uint8_t index = SIM868_SMS_ParseNewMsg(param);
	SIM868_SMS_RequestReceivedMsg(at, index);
	SIM868_SMS_DeleteMsg(at, index);
}

void SMS_MsgData(ATTerminal* at, char* param)
{
	SIM868SMSMessageInfo info         = SIM868_SMS_ParseMsgInfo(param);
	SMSMessage           msg          = {.Sender = info.Sender, .Message = {0}};
	SIM868_SMS_ReadMsg(at, msg.Message, info.Length);

	Observer_Publish(notifier, TOPIC_SMS_RECEIVED, &msg);
}
