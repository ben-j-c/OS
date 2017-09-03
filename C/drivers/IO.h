#ifndef _IO_
#define _IO_

unsigned char portInB(unsigned short port);
void portOutB(unsigned short port, unsigned char data);
unsigned short portInW(unsigned short port);
void portOutW ( unsigned short port , unsigned short data );

void io_wait();

#endif
