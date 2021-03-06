const char keyMap[] ={	'$', '~',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'+',
	'\b',
	'\t',
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n',
	's',
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	' ',
	'.',
	'.',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',
	'm',
	',',
	'.',
	'/',
	0xf0,
	'*',
	'.',
	' ',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
	'.',
};
#include "keyboardShift.c"

unsigned int getState(unsigned char keyCode);
void clearState(unsigned char keyCode);
void setState(unsigned char keyCode);

unsigned char keyState[0x80];

unsigned char charFromCode(unsigned char keyCode)
{
	if(getState(0x36) || getState(0x2A))
		return keyMapShift[keyCode];
	return keyMap[keyCode];
}

unsigned int getState(unsigned char keyCode)
{
	return (unsigned int) keyState[keyCode];
}

void clearState(unsigned char keyCode)
{
	keyState[keyCode] = 0;
}

void setState(unsigned char keyCode)
{
	keyState[keyCode] = 1;
}
