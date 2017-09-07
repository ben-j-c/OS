#include "time.h"

int getSeconds()
{
	portOutB(0x70, 0x00);
	io_wait();
	return portInB(0x71);
}
int getMinutes()
{
	portOutB(0x70, 0x02);
	io_wait();
	return portInB(0x71);
}
int getHours()
{
	portOutB(0x70, 0x04);
	io_wait();
	return portInB(0x71);
}
int getWeekday()
{
	portOutB(0x70, 0x06);
	io_wait();
	return portInB(0x71);
}
int getDayOfMonth()
{
	portOutB(0x70, 0x07);
	io_wait();
	return portInB(0x71);
}
int getMonth()
{
	portOutB(0x70, 0x08);
	io_wait();
	return portInB(0x71);
}
int getYear()
{
	portOutB(0x70, 0x09);
	io_wait();
	int y = portInB(0x71); 
	portOutB(0x70, 0x32);
	io_wait();
	return y + portInB(0x71)*100;
}

void getDate(Date * date)
{
	date->seconds = getSeconds();
	date->minutes = getMinutes();
	date->hours = getHours();
	date->weekday = getWeekday();
	date->dayOfMonth = getDayOfMonth();
	date->month = getMonth();
	date->year = getYear();
}
