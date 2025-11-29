#ifndef _HTTP_H_
#define _HTTP_H_

#include "atterminal.h"
#include "gps.h"

void HTTP_RequestDone(ATTerminal* at, char* param);

void HTTP_SetSession(ATTerminal* at, bool open);
bool HTTP_IsBusy();

void HTTP_PostLocation(const GPSInfo* info);
void HTTP_PostNotification(const char* title, const char* message);

#endif
