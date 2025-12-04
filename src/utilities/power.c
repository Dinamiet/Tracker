#include "config.h"
#include "pico/stdlib.h"
#include "tasks.h"
#include "utilities.h"

#include <stdio.h>

#define POWER_PIN       14
#define POWER_HOLD_TIME 2000

SchedulerTask powerTask;

void Power_Setup()
{
	gpio_init(POWER_PIN);
	gpio_put(POWER_PIN, false);
	gpio_set_dir(POWER_PIN, GPIO_OUT);

	Scheduler_CreateRecurringTask(scheduler, &powerTask, TASK_POWER_DEVICE, Power_On, NULL, CONFIG_GPS_FIX_INTERVAL * CONFIG_POWER_TIMEOUT * 1000);
}

void Power_On()
{
	printf("Power on\n");
	gpio_put(POWER_PIN, true);
	sleep_ms(POWER_HOLD_TIME);
	gpio_put(POWER_PIN, false);
}

void Power_Alive() { Scheduler_Refresh(scheduler, &powerTask); }
