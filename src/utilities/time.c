#include "utilities.h"

#include <time.h>

uint32_t Time_ms()
{
	struct timespec ts;

	clock_gettime(CLOCK_REALTIME, &ts);

	return (ts.tv_sec * 1000) + (ts.tv_nsec / 100000);
}
