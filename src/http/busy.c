#include "private.h"

static bool ongoingRequest = false;

bool HTTP_IsBusy() { return ongoingRequest; }

void HTTP_SetBusy(bool busy) { ongoingRequest = busy; }
