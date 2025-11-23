#include "comms.h"
#include "sim868_sms.h"
#include "sms.h"

void SMS_SendMsg(char* phoneNumber, char* msg) { SIM868_SMS_Send(atTerm, phoneNumber, msg); }
