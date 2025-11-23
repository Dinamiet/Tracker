#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "observer.h"
#include "topics.h"

#include <stdint.h>

extern Observer* notifier;

void     Utilities_Setup();
uint32_t Time_ms();

#endif
