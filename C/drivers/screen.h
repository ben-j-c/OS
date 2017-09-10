#ifndef DRIVER_SCREEN
#define DRIVER_SCREEN
#define SCREEN_SIZE 2000
#define VIDEO_MEMORY 0xb8000
#define OUT_VMA (0xb8000 + 2*SCREEN_SIZE)
#define ROWS 25
#define COLS 80
#define TAB_SIZE 4
#define TOTAL_BYTES 4000
#define WHITE_ON_BLACK 0x0f
#include "util/stream.h"

void printI32(int val);
void printI32_XYA(int value, int x, int y, char atrib);

void printX8(unsigned char hex);
void printX16(unsigned short hex);
void printX32(unsigned int hex);
void printX64(unsigned long long hex);

void printC(char c, int pos, char atrib);
void printX8_XYA(unsigned char hex, int x, int y, unsigned char atrib);
void printX16_XYA(unsigned short hex, int x, int y, unsigned char atrib);
void printX32_XYA(unsigned int hex, int x, int y, unsigned char atrib);
void printX64_XYA(unsigned long long hex, int x, int y, unsigned char atrib);


void print(const char* string);
void print_XYA(const char* string, int x, int y, char atrib);

void printf(const char * format, ...);
void printChar(char c);
void sprintChar(Stream* s, char c);
void setColour(char foreColour, char backColour);

void setAttrib(char value);
unsigned char getAttrib();
unsigned char getFG();
unsigned char getBG();

void clear();
void cls();
void clc();
void clearRange(int x, int y, int count);

int getOffset(int col, int row);
void scrollScreen();
void updateCursor();
void disableCursor();
void enableCursor();
void enableHexPrefix();
void disableHexPrefix();

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
#endif
