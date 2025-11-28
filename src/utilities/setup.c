#include "private.h"
#include "utilities.h"

Observer *notifier;
Observer ntfy;

void Utilities_Setup()
{
	notifier = &ntfy;
	Observer_Init(notifier);
	Power_Setup();
}
