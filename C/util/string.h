#ifndef _STRING_
#define _STRING_

int strcmp(char * p1, char* p2);
int streq(char* p1, char* p2);
char* toLower(char* p);
char* toUpper(char* p);
int firstOccurrence(char* subString, char* p1);
int strlen(char* p1);
int extractStringSection(char* p1, char split, int index, char* p2);
int atoi(unsigned char* number);



#endif
