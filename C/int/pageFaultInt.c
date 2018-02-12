#include "pageFaultInt.h"

void doubleFaultInt()
{
	print("We got a page fault!\n");
	
	while(1);//For the time being, we will just hang
	
	PIC_sendEOI_MASTER();PIC_sendEOI_SLAVE();
}
