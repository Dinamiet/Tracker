#include "comms.h"
#include "config.h"
#include "gsm.h"
#include "sim868_bearer.h"
#include "tasks.h"
#include "utilities.h"

#include <stdio.h>

static bool bearerInitialized = false;

static SchedulerTask internetConnectionTask;

static void connectionMonitor_Handler(void* _);

static void connectionMonitor_Handler(void* _)
{
	(void)_; // Unused

	SIM868_Bearer_QueryConnection(atTerm, CONFIG_CONNECTION_ID);
}

void GSM_ResetState() { bearerInitialized = false; }

void GSM_StartMonitor() { Scheduler_CreateRecurringTask(scheduler, &internetConnectionTask, TASK_INTERNET_CONNECTION_CHECK, connectionMonitor_Handler, NULL, CONFIG_INTERNET_CONNECTION_CHECK_PERIOD); }

void GSM_BearerConnectionStatus(ATTerminal* at, char* param)
{
	SIM868BearerStatusInfo info = SIM868_Bearer_ParseStatus(param);

	if (info.Identifier != CONFIG_CONNECTION_ID)
		return;

	printf("Internet connection ");
	switch (info.Status)
	{
		case SIM868_BEARER_STATUS_CLOSED:
			printf("closed\n");
			bearerInitialized = false;
			GSM_InternetConnect(at);
			break;

		case SIM868_BEARER_STATUS_CONNECTING:
		case SIM868_BEARER_STATUS_CLOSING:
			SIM868_Bearer_QueryConnection(at, CONFIG_CONNECTION_ID);
			break;

		case SIM868_BEARER_STATUS_CONNECTED:
			printf("connected\n");
			bearerInitialized = true;
			break;
	}
}

void GSM_InternetConnect(ATTerminal* at)
{
	SIM868_Bearer_OpenConnection(at, CONFIG_CONNECTION_ID, CONFIG_APN, SIM868_BEARER_CONNECTION_GPRS);
	printf("Opening Internet connection\n");
	SIM868_Bearer_QueryConnection(at, CONFIG_CONNECTION_ID);
}

bool GSM_InternetInitialized() { return bearerInitialized; }
