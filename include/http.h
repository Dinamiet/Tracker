#ifndef _HTTP_H_
#define _HTTP_H_

#include "atterminal.h"

void HTTP_RequestDone(ATTerminal* at, char* param);

void HTTP_SetSession(ATTerminal* at, bool open);

#endif
