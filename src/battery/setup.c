#include "battery.h"
#include "comms.h"
#include "config.h"
#include "sim868_misc.h"
#include "tasks.h"
#include "utilities.h"

static SchedulerTask batteryInfoRequestTask;

static void batteryRequest_Handler(void* _);

static void batteryRequest_Handler(void* _)
{
	(void)_; // Unused
	SIM868_Misc_BatteryStatus(atTerm);
}

void Battery_Setup() { Scheduler_CreateRecurringTask(scheduler, &batteryInfoRequestTask, TASK_BATTERY_INFO, batteryRequest_Handler, NULL, CONFIG_BATTERY_CHECK_PERIOD); }
