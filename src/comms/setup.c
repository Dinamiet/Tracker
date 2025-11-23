#include "comms.h"
#include "private.h"
#include "serial.h"
#include "sim868_misc.h"
#include "utilities.h"

ATTerminal*       atTerm;
static ATTerminal AT;

static ATTerminalResponseNotifier notifiers[] = {
		{SIM868_MISC_RESPONSE_RDY,   Ready_Handler},
		{					   0, Default_Handler}
};

static size_t terminal_read_handler(void* data, size_t size);
static size_t terminal_write_handler(void* data, size_t size);

static size_t terminal_read_handler(void* data, size_t size) { return Serial_Read(data, size); }

static size_t terminal_write_handler(void* data, size_t size) { return Serial_Write(data, size); }

void Comms_Setup()
{
	atTerm = &AT;
	ATTerminal_Init(atTerm, notifiers, terminal_read_handler, terminal_write_handler, Time_ms);
}
