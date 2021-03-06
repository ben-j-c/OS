#include "stream.h"

Stream* stdin = &kbStream;

char getc(Stream* s)
{
	int ret = 0;
	while(s->idxRemove == s->idxAdd);
		
	ret = s->offset[s->idxRemove];
	
	if(s->idxRemove + 1 == s->size)
		s->idxRemove = 0;
	else
		s->idxRemove++; 
	
	return ret;
}

int gets(Stream* s, char *buffer)
{	
	while(*buffer++ = getc(s));
}

void putc(Stream* s, char c)
{
	s->offset[s->idxAdd] = c;
	
	if(s->idxAdd + 1 == s->size)
		s->idxAdd= 0;
	else
		s->idxAdd++; 
}

char peekc(Stream* s)
{
	while(s->idxRemove == s->idxAdd);
	
	return s->offset[s->idxRemove];
}

void resetStream(Stream* s)
{
	for(int i = 0 ; i < s->size ; i++)
	{
		s->offset[i] = 0;
	}
	
	s->idxAdd = 0;
	s->idxRemove = 0;
}
