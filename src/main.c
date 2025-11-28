#include "comms.h"
#include "serial.h"
#include "tracking.h"
#include "utilities.h"

int main()
{
	Serial_Setup("/dev/ttyUSB0");

	Utilities_Setup();

	Comms_Setup();

	Tracking_Setup();

	Power_On();

	while (1)
	{
		SchedulerTask* nextTask = Scheduler_NextReady(scheduler);
		Scheduler_Execute(nextTask);
		Scheduler_Queue(scheduler, nextTask);
	}

	return 0;
}
