#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "atterminal.h"

void Battery_Setup();
void Battery_RequestInfo();
void Battery_Info(ATTerminal* at, char* param);

#endif
