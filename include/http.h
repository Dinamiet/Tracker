#ifndef _HTTP_H_
#define _HTTP_H_

#include "atterminal.h"

void HTTP_RequestDone(ATTerminal* at, char* param);

void HTTP_SetSession(ATTerminal* at, bool open);

void HTTP_PostData(char* url, void* data, size_t size);

#endif
