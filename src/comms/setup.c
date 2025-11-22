#include "comms.h"

#include "serial.h"
#include "utilities.h"

ATTerminal*       at;
static ATTerminal AT;

static ATTerminalResponseNotifier notifiers[] = {
		{0, NULL}
};

static size_t terminal_read_handler(void* data, size_t size);
static size_t terminal_write_handler(void* data, size_t size);

static size_t terminal_read_handler(void* data, size_t size) { return Serial_Read(data, size); }

static size_t terminal_write_handler(void* data, size_t size) { return Serial_Write(data, size); }

void Comms_Setup()
{
	at = &AT;
	ATTerminal_Init(at, notifiers, terminal_read_handler, terminal_write_handler, Time_ms);
}
