#ifndef _INT_PF_
#define _INT_PF_

#include "int/interruptInit.h"

extern void print(const char*);

extern void pageFaultIntWr(void);
void pageFaultInt(void);

#endif
