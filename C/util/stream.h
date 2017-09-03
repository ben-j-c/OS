#ifndef _STREAM_
#define _STREAM_

typedef struct Stream
{
	char* offset;
	int size;
	int idxAdd;
	int idxRemove;
} Stream;

static char kbBuffer[0x100];
static Stream kbStream = { kbBuffer, 0x100, 0, 0};

Stream* stdin;

char getc(Stream* s);
void putc(Stream* s, char c);
char peekc(Stream* s);
void resetStream(Stream* s);

#endif
