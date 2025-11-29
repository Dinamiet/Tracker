#ifndef _GPS_H_
#define _GPS_H_

#include "atterminal.h"

typedef struct _GPSInfo_
{
	bool     HasFix;
	uint32_t Timestamp;
	float    Altitude;
	float    Latitude;
	float    Longitude;
	float    Speed;
	float    Heading;
} GPSInfo;

void GPS_ResetState();

void GPS_PowerChange(ATTerminal* at, char* param);
void GPS_NewLocationInfo(ATTerminal* at, char* param);

void    GPS_Enable(bool enable);
GPSInfo GPS_GetInfo();
bool    GPS_Powered();

#endif
