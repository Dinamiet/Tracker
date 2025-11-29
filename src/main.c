#include "battery.h"
#include "comms.h"
#include "gsm.h"
#include "serial.h"
#include "tracking.h"
#include "utilities.h"

#include <stdio.h>

int main()
{
	Serial_Setup();

	Utilities_Setup();

	Comms_Setup();

	Tracking_Setup();
	Battery_Setup();

	GSM_StartMonitor();

	printf("Pico startup\n");

	while (1)
	{
		SchedulerTask* nextTask = Scheduler_NextReady(scheduler);
		Scheduler_Execute(nextTask);
		Scheduler_Queue(scheduler, nextTask);
	}

	return 0;
}
