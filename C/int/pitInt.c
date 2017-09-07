#include "pitInt.h"

unsigned long long systemTime = 0;
void pitInt(void)
{
	systemTime+= 1;
	clearRange(80-18, 23, 18);
	printX64_XYA(systemTime, 80-18, 24, 0xf0);
	PIC_sendEOI_MASTER();
}

unsigned long long getSystemTime()
{
	return systemTime;
}
