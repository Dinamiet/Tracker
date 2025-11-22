#include "private.h"

#include <stdio.h>

void Default_Handler(ATTerminal* at, char* param)
{
	(void)at; // Unused

	printf("Unhandled: '%s'\n", param);
}
