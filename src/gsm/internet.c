#include "config.h"
#include "gsm.h"
#include "sim868_bearer.h"

#include <stdio.h>

static bool bearerInitialized = false;

void GSM_InternetConnect(ATTerminal* at)
{
	SIM868_Bearer_OpenConnection(at, CONFIG_CONNECTION_ID, CONFIG_APN, SIM868_BEARER_CONNECTION_GPRS);
	bearerInitialized = true;
	printf("Opening Internet connection\n");
}

bool GSM_InternetInitialized() { return bearerInitialized; }
