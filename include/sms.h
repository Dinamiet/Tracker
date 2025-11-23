#ifndef _SMS_H_
#define _SMS_H_

#include "atterminal.h"

typedef struct _SMSMessage_
{
	char* Sender;
	char  Message[128];
} SMSMessage;

void SMS_ReceivedNewMsg(ATTerminal* at, char* param);
void SMS_MsgData(ATTerminal* at, char* param);

void SMS_SendMsg(char* phoneNumber, char* msg);

#endif
