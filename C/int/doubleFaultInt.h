#ifndef _INT_DF_
#define _INT_DF_

#include "int/interruptInit.h"

extern void print(const char*);

extern void doubleFaultIntWr(void);
void doubleFaultInt(void);

#endif
