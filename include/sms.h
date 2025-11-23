#ifndef _SMS_H_
#define _SMS_H_

#include "atterminal.h"

void SMS_ReceivedNewMsg(ATTerminal* at, char* param);
void SMS_MsgData(ATTerminal* at, char* param);

#endif
