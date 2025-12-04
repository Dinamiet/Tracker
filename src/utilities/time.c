#include "utilities.h"

#if 0

uint32_t Time_ms()
{
	struct timespec ts;

	clock_gettime(CLOCK_REALTIME, &ts);

	return (ts.tv_sec * 1000) + (ts.tv_nsec / 100000);
}

#else

#include <pico/time.h>

uint32_t Time_ms() { return to_ms_since_boot(get_absolute_time()); }

#endif
