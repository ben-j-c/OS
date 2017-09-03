#include "IO.h"

unsigned char portInB(unsigned short port)
{
	unsigned char data;
	__asm__("in %%dx, %%al" : "=a" (data) : "d" (port));
	
	return data;
}

void portOutB(unsigned short port, unsigned char data)
{
	__asm__("out %%al ,%%dx" : : "a" (data), "d" (port));
}

unsigned short portInW(unsigned short port)
{
	unsigned short data;
	__asm__("in %%dx, %%al" : "=a" (data) : "d" (port) );
	return data;
}

void portOutW ( unsigned short port , unsigned short data )
{
	__asm__ ("out %%ax, %%dx" : : "a" ( data ), "d" ( port ));
}

void io_wait(void)
{
    /* This came from osdev.  I really dislike how the author documents*/
    __asm__ volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}
