#include "call.h"
#include "comms.h"
#include "gsm.h"
#include "private.h"
#include "serial.h"
#include "sim868_call.h"
#include "sim868_gsm.h"
#include "sim868_misc.h"
#include "utilities.h"

ATTerminal*       atTerm;
static ATTerminal AT;

static ATTerminalResponseNotifier notifiers[] = {
		{		   SIM868_MISC_RESPONSE_RDY,     Ready_Handler},
		{		   SIM868_GSM_RESPONSE_FUNC,              NULL}, // Ignore
		{			SIM868_GSM_RESPONSE_PIN,              NULL}, // Ignore
		{  SIM868_GSM_RESPONSE_NETWORKCHANGE, GSM_NetworkChange},
		{		 SIM868_CALL_RESPONSE_READY,  Call_Initialized},
		{		  SIM868_CALL_RESPONSE_RING,              NULL}, // Ignore
		{SIM868_CALL_RESPONSE_IDENTIFICATION,     Call_Incoming},
		{								  0,   Default_Handler}
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
