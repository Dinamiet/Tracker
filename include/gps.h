#ifndef _GPS_H_
#define _GPS_H_

#include "atterminal.h"

void GPS_PowerChange(ATTerminal* at, char* param);
void GPS_NewLocationInfo(ATTerminal* at, char* param);

#endif
