#include "pico/stdlib.h"
#include "utilities.h"

#include <stdio.h>

#define POWER_PIN       14
#define POWER_HOLD_TIME 2000

void Power_Setup()
{
	gpio_init(POWER_PIN);
	gpio_put(POWER_PIN, false);
	gpio_set_dir(POWER_PIN, GPIO_OUT);
}

void Power_On()
{
	printf("Power on\n");
	gpio_put(POWER_PIN, true);
	sleep_ms(POWER_HOLD_TIME);
	gpio_put(POWER_PIN, false);
}
