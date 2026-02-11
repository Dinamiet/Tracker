#include "config.h"
#include "hardware/watchdog.h"
#include "pico/stdlib.h"
#include "tasks.h"
#include "utilities.h"

#include <stdio.h>

#define HEARTBEAT_LED 25

static SchedulerTask heartbeatTask;
static size_t        ledToggle = 0;

static void heartbeat_Handler(void* _);

static void heartbeat_Handler(void* _)
{
	(void)_; // Unused
	gpio_put(HEARTBEAT_LED, ledToggle++ & 1);
	watchdog_update();
}

void HeartBeat_Setup()
{
	gpio_init(HEARTBEAT_LED);
	gpio_put(HEARTBEAT_LED, false);
	gpio_set_dir(HEARTBEAT_LED, GPIO_OUT);

	if (watchdog_caused_reboot())
		printf("Watchdog reboot\n");

	watchdog_enable(CONFIG_WATCHDOG_TIMEOUT, true);

	Scheduler_CreateRecurringTask(scheduler, &heartbeatTask, TASK_HEARTBEAT, heartbeat_Handler, NULL, 500);
}
