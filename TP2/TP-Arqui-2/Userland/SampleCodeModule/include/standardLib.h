#ifndef STANDARD_LIB_H
#define STANDARD_LIB_H

#include <stdint.h>
//#include <string.h>
#include <stdarg.h>
#include <libasm.h>

#define DEFAULT_FONT_COLOR 0xFFFFFF
#define DEFAULT_BACKGROUND_COLOR 0x000000
#define DELETE_KEY 0x0E
#define DELETE_KEY_RELEASED 0xFFFFFFFFFFFFFF8E

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 764
#define CHAR_HEIGHT 16

void putChar(char str);
char getChar();

void printf(const char *format, ...);
int scanf(const char *format, ...);
int strToInt(char *charValue);
int numToStr(char *str, int num);
int strcmp(char *s1, char *s2);
void setFontColor(int color);
void setBackGroundColor(int color);
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);
int numToBase(uint64_t value, uint_least32_t base, uint64_t *buffer);
void error(char *str1, char *str2);
char *strcpy(char *destination, const char *source);

int getDistance(int to, int from);
// void hexaTo2(char *buff, int dim);
void parseHexa(char *buff, int dim);
void printBase(uint64_t value, uint_least32_t base);
void printmem();
void printTime();
long getMillis();

int createProcess(char *name, void *func, int argc, char *argv[]);

#endif
