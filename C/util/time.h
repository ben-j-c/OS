#ifndef _TIME_
#define _TIME_

#include "drivers/IO.h"

typedef struct
{
	char seconds, minutes, hours, weekday, dayOfMonth, month;
	int year;
} Date;

int getSeconds();
int getMinutes();
int getHours();
int getWeekday();
int getDayOfMonth();
int getMonth();
int getYear();
void getDate(Date*);

#endif
