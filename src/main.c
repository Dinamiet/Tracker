#include "comms.h"
#include "serial.h"
#include "utilities.h"

int main()
{
	Serial_Setup("/dev/ttyUSB0");

	Utilities_Setup();

	Comms_Setup();

	while (1) { Comms_Process(); }

	return 0;
}
