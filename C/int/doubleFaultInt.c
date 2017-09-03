#include "doubleFaultInt.h"

void doubleFaultInt()
{
	print("We got a double fault!\n");
	
	PIC_sendEOI_MASTER();
}
