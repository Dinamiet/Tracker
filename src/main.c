#include "comms.h"
#include "serial.h"

int main()
{
	Serial_Setup("/dev/ttyUSB0");

	Comms_Setup();

	while (1) { Comms_Process(); }

	return 0;
}
