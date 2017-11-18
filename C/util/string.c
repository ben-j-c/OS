#include "string.h"

int strcmp(char* p1, char* p2 )
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;


	while((c1 = *s1++) == (c2 = *s2++) && c1 != '\0');
	
	return c1 - c2;
}

int streq(char* p1, char* p2)
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	
	while(*s1 && *s1++ == *s2++);
	
	if(!(*s2 || *s1))
		return 1;
		
	return 0;
	
}

char* toUpper(char* p1)
{
	unsigned char *s1 = (unsigned char *) p1;
	while(*s1)
	{
		if(*s1 >= 'a' && *s1 <= 'z')
		{
			*s1 = *s1 - 0x20;
		}
		
		s1++;
	}
	
	//print(p1);
	//print("\n");
	return p1;
}

char* toLower(char* p1)
{
	unsigned char *s1 = (unsigned char *) p1;
	while(*s1)
	{
		if(*s1 >= 'A' && *s1 <= 'Z')
		{
			*s1 = *s1 + 0x20;
		}
		
		s1++;
	}
	
	//print(p1);
	//print("\n");
	return p1;
}

int firstOccurrence(char* subString, char* p1)
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2;
	
	int count = 0;
	while(*s1)
	{
		s2 = (const unsigned char *) subString;
		while(*s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		if(!*s2)
			return count;
		
		
		count++;
		s1++;
	}
	
	return -1;
	
}
int strlen(char* p1)
{
	const unsigned char *s1 = (const unsigned char *) p1;
	
	while(*s1)s1++;
	
	return (int)s1 - (int)p1;
}

int extractStringSection(char* p1, char split, int index, char* p2)
{
	const unsigned char *s1 = (const unsigned char*) p1;
	const unsigned char *s2 = (const unsigned char*) p2;
	unsigned char c = (unsigned char) split;
	
	int count = 0;
	
	while(count != index && *s1++)
	{
		if(*(s1 - 1) == c)
			count++;
	}
	
	if(!*s1)
		return -1;
	
	while(*s1 && *s1 != c)
	{
		*p2++ = *s1++;
	}
	*p2 = 0;
	
	return 0;
}

int atoi(unsigned char* number)
{
	int value = 0;
	
	if(*number == '0' && (*(number + 1) == 'x' || *(number + 1) == 'X'))
	{
		number = number + 2;
		int counter = 0;
		
		while(*number)
		{
			unsigned char cur = *number;
			if(cur >= '0' && cur <= '9')
				value = (value << 4) + cur - '0';
			else if(cur >= 'A' && cur <= 'F')
				value = (value << 4) + cur - 'A' + 10;
			else if(cur >= 'a' && cur <= 'a')
				value = (value << 4) + cur - 'a' + 10;
			
			number++;
		}
	}
	else
	{
	}
	
	return value;
}
