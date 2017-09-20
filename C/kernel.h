#ifndef _KERNEL_
#define _KERNEL_
#define NULL 0
#define null 0
#define true 1
#define TRUE 1
#define false 0
#define FALSE 0


#include "util/stream.h"
#include "util/string.h"
#include "util/time.h"
#include "drivers/IO.h"
#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "drivers/PIT.h"
#include "int/interruptInit.h"
#include "int/keyboardInt.h"

void interruptInit(void);
static void loop(void);
void system(Stream *cmd);
static void printTime(void);
static void printMemoryMap(void);
static void init(void) __attribute((section(".start")));


typedef struct
{
	unsigned long long baseAddress;
	unsigned long long length;
	unsigned int regionType;
} MemoryRegion;

#endif
