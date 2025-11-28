#include "pico/stdlib.h"
#include "tasks.h"
#include "utilities.h"

#define HEARTBEAT_LED 25

static SchedulerTask heartbeatTask;
static size_t ledToggle = 0;

static void heartbeat_Handler(void* _);

static void heartbeat_Handler(void* _)
{
	(void)_; // Unused
	gpio_put(HEARTBEAT_LED, ledToggle++ & 1);
}

void HeartBeat_Setup()
{
	gpio_init(HEARTBEAT_LED);
	gpio_put(HEARTBEAT_LED, false);
	gpio_set_dir(HEARTBEAT_LED, GPIO_OUT);

	Scheduler_CreateRecurringTask(scheduler, &heartbeatTask, TASK_HEARTBEAT, heartbeat_Handler, NULL, 500);
}
