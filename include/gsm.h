#ifndef _GSM_H_
#define _GSM_H_

#include "atterminal.h"

void GSM_ResetState();

void GSM_EnableNetworkStatusUpdates(ATTerminal* at, bool enable);
void GSM_NetworkChange(ATTerminal* at, char* param);

void GSM_InternetConnect(ATTerminal* at);
bool GSM_InternetInitialized();

#endif
