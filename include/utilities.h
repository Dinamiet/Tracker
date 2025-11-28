#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "observer.h"
#include "scheduler.h"
#include "topics.h"

#include <stdint.h>

extern Observer* notifier;
extern Scheduler* scheduler;

void     Utilities_Setup();
uint32_t Time_ms();
void     Power_On();

#endif
