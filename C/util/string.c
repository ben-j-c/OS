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
	
}
