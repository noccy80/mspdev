#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <stdint.h>

#define NUM_PRESETS 8
#define MAX_DISPLAY 512
typedef struct DBMESSAGE {
	const char* string;
	uint8_t length;
} DbMessage;

#endif // __DATABASE_H__
