#include "kernel.h"

char cmd_array[64];
Stream cmd;

void interruptInit();
static void loop();
void system(Stream *cmd);
static void printTime();
static void printMemoryMap();


typedef struct
{
	unsigned long long baseAddress;
	unsigned long long length;
	unsigned int regionType;
} MemoryRegion;

static MemoryRegion *memory = (MemoryRegion*) 0x504;

void init()
{	
	clear();
	enableCursor();
	disableHexPrefix();
	print("init: ");
	printX32((unsigned int) init);
	print("\n");
	
	print("System memory map: ");
	printI32(*(unsigned int*) 0x500);
	print("\n");
	
	interruptInit();
	setCh0(0x0020);
	print("Successfully loaded interrupt table\n");
	print("12345    112345    212345    312345    412345    512345    612345    712345    8");
	
	setColour(0xf,0x4);
	print("The system has now booted...\n");
	setColour(0xf,0x0);
	
	loop();
}

void loop()
{
	cmd.idxAdd = 0;
	cmd.idxRemove = 0;
	cmd.offset = cmd_array;
	cmd.size = 64;
	
	unsigned long long lastTime = getSystemTime();
	while(1)
	{
		
		unsigned char cur = getc(stdin);
		printChar(cur);
		if(cur != '\n')
		{
			sprintChar(&cmd, cur);
		}
		else
		{
			putc(&cmd, '\0');
			system(&cmd);
			clearRange(0, 24, 64);
		}
	}
}

void system(Stream* cmd)
{
	char buffer[64];
	gets(cmd, buffer);
	toUpper(buffer);
	
	if(streq(buffer, "CLEAR"))
	{
		clear();
	}
	else if(streq(buffer, "HELLO"))
	{
		print("HELLO!\n");
	}
	else if(streq(buffer, "TIME"))
	{
		printTime();
	}
	else if(streq(buffer, "MEMORY"))
	{
		printMemoryMap();
	}
	else if(streq(buffer, "INC FG"))
	{
		setColour(getFG() + 1, getBG());
	}
	else if(streq(buffer, "INC BG"))
	{
		setColour(getFG(), getBG() + 1);
	}
	else if(streq(buffer, "GET SCREEN_ATRIB"))
	{
		printX8(getAttrib());
		printChar('\n');
	}
		
}

static void printMemoryMap()
{
	for(int i = 0; i < *(unsigned int*) 0x500 ;i++)
	{
		printX64(memory[i].baseAddress);
		printChar(' ');
		printX64(memory[i].length);
		printChar(' ');
		printX32(memory[i].regionType);
		printChar('\n');
	}
}

static void printTime()
{
	Date d;
	
	getDate(&d);
	
	printX8(d.hours);
	print(":");
	printX8(d.minutes);
	print("\n");
}
