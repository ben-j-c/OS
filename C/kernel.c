#include "kernel.h"

#define NULL 0
#define null 0

char cmd_array[64];
Stream cmd;

void interruptInit();
static void loop();
void system(Stream *cmd);
static void printTime();

void init()
{	
	clear();
	enableCursor();
	disableHexPrefix();
	print("init: ");
	printX32((unsigned int) init);
	print("\n");
	interruptInit();
	setCh0(0x0020);
	print("Successfully loaded interrupt table\n");
	print("12345    112345    212345    312345    412345    512345    612345    712345    8");
	
	setColour(0xf,0x4);
	print("\n\nWaiting until 0x1000...\n");
	setColour(0xf,0x0);
	
	
	
	for(;((int)getSystemTime()) < 0x1000;);
	clear();
	
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
	
	
	if(!strcmp(buffer, "clear"))
		clear();
	else if(!strcmp(buffer, "hello"))
		print("HELLO!\n");
	else if(!strcmp(buffer, "time"))
		printTime();
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
