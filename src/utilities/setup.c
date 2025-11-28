#include "private.h"
#include "utilities.h"

Observer* notifier;
Observer  ntfy;

Scheduler* scheduler;
Scheduler  schd;

void Utilities_Setup()
{
	notifier  = &ntfy;
	scheduler = &schd;
	Observer_Init(notifier);
	Scheduler_Init(scheduler, Time_ms);
	Power_Setup();
}
