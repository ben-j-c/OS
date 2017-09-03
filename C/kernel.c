#include "kernel.h"

#define NULL 0
#define null 0

char cmd_array[64];
Stream cmd;

void interruptInit();
void loop();
void system();

void init()
{	
	clear();
	enableCursor();
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
			putc(&cmd, NULL);
			system(cmd.offset);
			resetStream(&cmd);
			clearRange(0, 24, 64);
		}
	}
}

void system(char* cmd)
{
	if(!strcmp(cmd, "clear"))
		clear();
	else if(!strcmp(cmd, "hello"))
		print("HELLO!\n");
}
