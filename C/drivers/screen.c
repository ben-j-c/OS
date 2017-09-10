#include "screen.h"
#include "IO.h"

static int cursorIdx = 0;
static const char mapping[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
static struct 
{
	unsigned int displayCursor : 1;
	unsigned int displayHexPrefix: 1;
} options;
static unsigned char lastAttrib = WHITE_ON_BLACK;

/**
 * Print specific values at specific locations
 * 
 */

void printC(char c, int pos, char attrib)
{
	volatile unsigned char *vm = (volatile unsigned char*) VIDEO_MEMORY;
	
	vm[pos << 1] = c;
	vm[(pos << 1) + 1] = attrib;
}

void printI32(int value)
{
	char sign = '+';
	
	if(value < 0)
	{
		value = -value;
		sign = '-';
	}
	
	char c[] = {'0','0','0','0','0','0','0','0','0','0'};
	for(int i = 0 ; i < 11 ; i++)
	{
		c[i] = '0' + value%10;
		value /= 10;
	}
	
	int start = 11;
	
	while(c[--start] == '0'  && start > 0);
	
	if(sign == '-')
	{
		printChar(sign);
	}
	
	for(int i = start; i >= 0; i--)
	{
		printChar(c[i]);
	}
}

void printI32_XYA(int value, int x, int y, char atrib)
{
	int pos = getOffset(x,y);
	
	char sign = '+';
	
	if(value < 0)
	{
		value = -value;
		sign = '-';
	}
	
	char c[] = {'0','0','0','0','0','0','0','0','0','0'};
	for(int i = 0 ; i < 11 ; i++)
	{
		c[i] = '0' + value%10;
		value /= 10;
	}
	
	int start = 11;
	
	while(c[--start] == '0'  && start > 0);
	
	if(sign == '-')
	{
		printC(sign, pos++, atrib);
	}
	
	for(int i = start; i >= 0; i--)
	{
		printC(c[i], pos++, atrib);
	}
}

void printX8(unsigned char value)
{
	int shift = 4;
	
	if(options.displayHexPrefix)
	{
		printChar('0');
		printChar('x');
	}
	
	while(shift != -4)
	{
		char c = mapping[0x0f & (value >> shift)];
		printChar(c);
		shift -= 4;
	}
}

void printX16(unsigned short value)
{
	int shift = 12;
	
	if(options.displayHexPrefix)
	{
		printChar('0');
		printChar('x');
	}
	
	while(shift != -4)
	{
		char c = mapping[0x0f & (value >> shift)];
		printChar(c);
		shift -= 4;
	}
}

void printX32(unsigned int value)
{
	char mapping[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	int shift = 28;
	
	if(options.displayHexPrefix)
	{
		printChar('0');
		printChar('x');
	}
	
	while(shift != -4)
	{
		char c = mapping[0x0f & (value >> shift)];
		printChar(c);
		shift -= 4;
	}
}

void printX64(unsigned long long value)
{
	int shift = 60;
	
	if(options.displayHexPrefix)
	{
		printChar('0');
		printChar('x');
	}
	
	while(shift != -4)
	{
		char c = mapping[0x0f & (value >> shift)];
		printChar(c);
		shift -= 4;
	}
}

void printX8_XYA(unsigned char value, int x, int y, unsigned char atrib)
{
	int pos = y*COLS + x;
	
	if(pos >= 0 && (pos + 10) < SCREEN_SIZE)
	{
		int shift = 4;
		
		if(options.displayHexPrefix)
		{
			printC('0',pos++,atrib);
			printC('x',pos++,atrib);
		}
		
		while(shift != -4)
		{
			char c = mapping[0x0f & (value >> shift)];
			printC(c, pos++, atrib);
			shift -= 4;
		}
	}
	
}

void printX16_XYA(unsigned short value, int x, int y, unsigned char atrib)
{
	int pos = y*COLS + x;
	
	if(pos >= 0 && (pos + 10) < SCREEN_SIZE)
	{
		int shift = 12;
		
		if(options.displayHexPrefix)
		{
			printC('0',pos++,atrib);
			printC('x',pos++,atrib);
		}
		
		while(shift != -4)
		{
			char c = mapping[0x0f & (value >> shift)];
			printC(c, pos++, atrib);
			shift -= 4;
		}
	}
	
}

void printX32_XYA(unsigned int value, int x, int y, unsigned char atrib)
{
	int pos = y*COLS + x;
	
	if(pos >= 0 && (pos + 10) < SCREEN_SIZE)
	{
		int shift = 28;
		
		if(options.displayHexPrefix)
		{
			printC('0',pos++,atrib);
			printC('x',pos++,atrib);
		}
		
		while(shift != -4)
		{
			char c = mapping[0x0f & (value >> shift)];
			printC(c, pos++, atrib);
			shift -= 4;
		}
	}
	
}

void printX64_XYA(unsigned long long value, int x, int y, unsigned char atrib)
{
	int pos = y*COLS + x;
	
	if(pos >= 0 && (pos + 10) < SCREEN_SIZE)
	{
		int shift = 60;
		
		if(options.displayHexPrefix)
		{
			printC('0',pos++,atrib);
			printC('x',pos++,atrib);
		}
		
		while(shift != -4)
		{
			char c = mapping[0x0f & (value >> shift)];
			printC(c, pos++, atrib);
			shift -= 4;
		}
	}
}

/**
 * 
 * Print strings using the cursor
 * 
 */
 
static int getIncrementCursor()
{
	int ret = cursorIdx++;
	if(cursorIdx >= SCREEN_SIZE)
	{
		scrollScreen();
		ret = cursorIdx;
	}
	updateCursor();
	return ret;
}

static int getDecrementedCursor()
{
	if(cursorIdx <= 0)
	{
		cursorIdx = 0;
	}
	else
	{
		cursorIdx--;
	}
	
	updateCursor();
	return cursorIdx;
}

int getCursor()
{
	return cursorIdx;
}

void zeroCursor()
{
	cursorIdx = 0;
	updateCursor();
}

void newLine()
{
	cursorIdx = (cursorIdx/COLS + 1)*COLS;
	if(cursorIdx >= SCREEN_SIZE)
	{
		scrollScreen();
	}
	
	updateCursor();
}

void printChar(char c)
{
	volatile unsigned char *vm = (volatile unsigned char*) VIDEO_MEMORY;
	
	if(c == '\n')
	{
		newLine();
	}
	else if(c == '\t')
	{
		for(int i = getCursor()%TAB_SIZE ; i < TAB_SIZE ; i++)
			printChar(' ');
	}
	else if(c == '\b')
	{
		int cursor = getDecrementedCursor();
		*(vm + 2*cursor) = 0;
		*(vm + 2*cursor+1) = lastAttrib;
	}
	else
	{
		int cursor = getIncrementCursor();
		*(vm + 2*cursor) = c;
		*(vm + 2*cursor+1) = lastAttrib;
	}
	
}

void sprintChar(Stream* s, char c)
{
	if(c == '\b')
	{
		if(s->idxAdd != s->idxRemove)
		{
			s->offset[s->idxAdd] = 0;
			s->idxAdd--;
		}
	}
	else
	{
		putc(s, c);
	}
}

void print(const char* string)
{
	char c;
	while((c = *string++))
		printChar(c);
}

void print_XYA(const char* string, int x, int y, char atrib)
{
	volatile unsigned char *vm = (volatile unsigned char*) (VIDEO_MEMORY + getOffset(x,y));
	char c;
	while( c = *string++)
	{
		*vm++ = c;
		*vm++ = atrib;
	}
}

void clear()
{
	volatile unsigned char *vm = (volatile unsigned char*) VIDEO_MEMORY;
	
	for(int i = 0 ;  i < 2000 ; i++)
	{
		*(vm + (i << 1)) = (unsigned char) 0x00;
		*(vm + (i << 1) + 1 ) = (unsigned char) 0x0f;
	}
	
	zeroCursor();
}

void clearRange(int x, int y, int count)
{
	volatile unsigned char *vm = (volatile unsigned char*) (VIDEO_MEMORY + getOffset(x,y));
	while(count-- > 0)
	{
		*vm++ = 0;
		*vm++ = WHITE_ON_BLACK;
	}
}

void setColour(char foreColour, char backColour)
{
	lastAttrib = (foreColour & 0x0f) | (backColour & 0x0f) << 4;
}

void setAttrib(char value)
{
	lastAttrib = value;
}

unsigned char getAttrib()
{
	return lastAttrib;
}

unsigned char getFG()
{
	return lastAttrib & 0x0f;
}
unsigned char getBG()
{
	return (lastAttrib & 0xf0) >> 4;
}

void cls()
{
	clear();
}

void clc()
{
	clear();
}

/**
 * converts an xy to a linear offset from 
 */
int getOffset(int col, int row)
{
	if(col < 0 || row < 0 || col >= COLS || row >= ROWS)
		return 0;
	return (col + row*COLS) << 1;
}

void scrollScreen()
{
	volatile unsigned char *vm = (volatile unsigned char*) VIDEO_MEMORY;
	
	for(int row = 0 ; row < (ROWS - 1) ; row++)
	{
		for(int col = 0 ; col < COLS ; col++)
		{
			int low = 2*(row*COLS + col);
			int high = 2*(row*COLS + col + COLS);
			*(vm + low) = *(vm + high);
			*(vm + low+1) = *(vm + high+1);
		}
	}
	
	for(int i = 0 ; i < COLS ; i++)
	{
		*(vm + 2*(i + (ROWS - 1)*COLS)) = 0;
		*(vm + 2*(i + (ROWS - 1)*COLS) + 1) = WHITE_ON_BLACK;
	}
	
	cursorIdx -= COLS;
	if(cursorIdx < 0)
		cursorIdx = 0;
		
	updateCursor();
}

void updateCursor()
{
	if(options.displayCursor)
	{
		portOutB(0x3D4, 0x0F);
	    portOutB(0x3D5, (unsigned char)(cursorIdx&0xFF));
	    portOutB(0x3D4, 0x0E);
	    portOutB(0x3D5, (unsigned char )((cursorIdx>>8)&0xFF));
	}
	else
	{
		portOutB(0x3D4, 0x0F);
	    portOutB(0x3D5, 0xFF);
	    portOutB(0x3D4, 0x0E);
	    portOutB(0x3D5, 0xFF);
	}
}

void enableCursor()
{
	options.displayCursor = 1;
}

void disableCursor()
{
	options.displayCursor = 0;
}

void enableHexPrefix()
{
	options.displayHexPrefix = 1;
}
void disableHexPrefix()
{
	options.displayHexPrefix = 0;
}
