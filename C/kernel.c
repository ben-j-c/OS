#include "kernel.h"
#include "paging.c"

char cmd_array[64];
Stream cmd;

static void init(void)
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
	
	startPaging();
	print("Successfully started paging\n");
	
	setColour(0xf,0x4);
	print("The system has now booted...\n");
	setColour(0xf,0x0);
	
	loop();
}

static void loop()
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
	char command[64];
	gets(cmd, command);
	toUpper(command);
	
	extractStringSection(command, ' ', 0, buffer);
	
	
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
	else if(streq(buffer, "INC"))
	{
		if(extractStringSection(command, ' ', 1, buffer))
			return;
		
		if(streq(buffer, "FG"))
			setColour(getFG() + 1, getBG());
		else if(streq(buffer, "BG"))
			setColour(getFG(), getBG() + 1);
	}
	else if(streq(buffer, "GET"))
	{
		if(extractStringSection(command, ' ', 1, buffer))
			return;
		
		if(streq(buffer, "SCREEN_ATRIB"))
			printX8(getAttrib());
		else if(streq(buffer, "ADDR"))
		{
			if(extractStringSection(command, ' ', 2, buffer))
				return;
			printX8(*(unsigned char*)atoi(buffer));
		}
		printChar('\n');
	}
	else if(streq(buffer, "SET"))
	{
		if(extractStringSection(command, ' ', 1, buffer))
			return;
		
		if(streq(buffer, "SCREEN_ATRIB"))
		{
			if(extractStringSection(command, ' ', 2, buffer))
				return;
				
			setAttrib((char) atoi(buffer));
		}
		else if(streq(buffer, "ADDR"))
		{
			if(extractStringSection(command, ' ', 2, buffer))
				return;
			unsigned char* addr = (unsigned char*)atoi(buffer);
			
			if(extractStringSection(command, ' ', 3, buffer))
				return;
			*addr = (unsigned char) atoi(buffer);
		}
	}
		
}

static void printMemoryMap()
{
	print("Memory map:\nBase Address,    Length,          Region Type\n");
	for(int i = 0; i < *memoryRegions ;i++)
	{
		
		printX64(memoryRegionDesc[i].baseAddress);
		printChar(' ');
		printX64(memoryRegionDesc[i].length);
		printChar(' ');
		printX32(memoryRegionDesc[i].regionType);
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
