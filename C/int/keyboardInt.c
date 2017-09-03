#include "keyboardInt.h"
#include "mapping/keyboard.c"

void keyboardInt(void)
{
	unsigned char keyCode = (unsigned char) portInB(0x60);
	
	//printX32(keyCode);
	//print("\n");
	if(keyCode < 0x80)
	{
		setState(keyCode);
		char c = charFromCode(keyCode);
		if(keyCode != 0x36 && keyCode != 0x2A)
			putc(stdin, c);
	}
	else
	{
		clearState(keyCode - 0x80);
	}
	
	PIC_sendEOI_MASTER();
}
