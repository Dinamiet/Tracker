#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdint.h>
#include <stddef.h>

void Serial_Setup(const char* fileName);
size_t Serial_Write(const void* data, size_t length);
size_t Serial_Read(void* data, size_t length);

#endif
