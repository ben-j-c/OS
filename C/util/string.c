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
	
	if(*s1 == *s2)
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
