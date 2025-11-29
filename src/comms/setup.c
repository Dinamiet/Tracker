#include "battery.h"
#include "call.h"
#include "comms.h"
#include "gps.h"
#include "gsm.h"
#include "http.h"
#include "private.h"
#include "serial.h"
#include "sim868_bearer.h"
#include "sim868_call.h"
#include "sim868_gps.h"
#include "sim868_gsm.h"
#include "sim868_http.h"
#include "sim868_misc.h"
#include "sim868_sms.h"
#include "sms.h"
#include "tasks.h"
#include "utilities.h"

ATTerminal*          atTerm;
static ATTerminal    AT;
static SchedulerTask terminalTask;

static ATTerminalResponseNotifier notifiers[] = {
		{		   SIM868_MISC_RESPONSE_RDY,              Ready_Handler},
		{		   SIM868_GSM_RESPONSE_FUNC,                       NULL}, // Ignore
		{			SIM868_GSM_RESPONSE_PIN,                       NULL}, // Ignore
		{  SIM868_GSM_RESPONSE_NETWORKCHANGE,          GSM_NetworkChange},
		{		 SIM868_CALL_RESPONSE_READY,           Call_Initialized},
		{		  SIM868_CALL_RESPONSE_RING,                       NULL}, // Ignore
		{SIM868_CALL_RESPONSE_IDENTIFICATION,              Call_Incoming},
		{		  SIM868_SMS_RESPONSE_READY,                       NULL}, // Ignore
		{        SIM868_SMS_RESPONSE_NEW_MSG,         SMS_ReceivedNewMsg},
		{       SIM868_SMS_RESPONSE_MSG_DATA,                SMS_MsgData},
		{		   SIM868_SMS_RESPONSE_SENT,                       NULL}, // Ignore
		{		  SIM868_GPS_RESPONSE_POWER,            GPS_PowerChange},
		{			SIM868_GPS_RESPONSE_FIX,        GPS_NewLocationInfo},
		{ SIM868_HTTP_RESPONSE_ACTION_STATUS,           HTTP_RequestDone},
		{SIM868_MISC_RESPONSE_BATTERY_STATUS,               Battery_Info},
		{      SIM868_BEARER_RESPONSE_STATUS, GSM_BearerConnectionStatus},
		{								  0,			Default_Handler}
};

static size_t terminal_read_handler(void* data, size_t size);
static size_t terminal_write_handler(void* data, size_t size);
static void   process_handler(void* _);

static size_t terminal_read_handler(void* data, size_t size) { return Serial_Read(data, size); }

static size_t terminal_write_handler(void* data, size_t size) { return Serial_Write(data, size); }

static void process_handler(void* _)
{
	(void)_; // Unused
	Comms_Process();
}

void Comms_Setup()
{
	atTerm = &AT;
	ATTerminal_Init(atTerm, notifiers, terminal_read_handler, terminal_write_handler, Time_ms);

	Scheduler_CreateRecurringTask(scheduler, &terminalTask, TASK_TERMINAL_PROCESS_ID, process_handler, NULL, 0);
}
