#ifndef _INT_KEYB_
#define _INT_KEYB_
#define KEY_STREAM_SIZE 0x100

#include "util/stream.h"
#include "int/interruptInit.h"

extern void printI32(int val);
extern void printX32(unsigned int);
extern void print(const char*);
extern void printChar(char c);

extern void portOutB(unsigned short port, unsigned char data);
extern unsigned char portInB(unsigned short port);

extern void keyboardIntWr(void);
void keyboardInt(void);

#endif
