#ifndef _INT_PIT_
#define _INT_PIT_

#include "int/interruptInit.h"

extern void print(const char*);
extern void printX64_XYA(unsigned long long, int x, int y, unsigned char atrib);

extern void pitIntWr(void);
void pitInt(void);
unsigned long long getSystemTime();

#endif
