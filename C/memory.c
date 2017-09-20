#include "memory.h"

void* malloc(unsigned int size)
{
	
}

void* calloc(unsigned int size)
{
	
}

void* ralloc(void*, unsigned int size)
{
	
}

void* memset(void* p, unsigned int size, unsigned char value)
{
	while(size-- > 0)
		*p++ = value;
}
