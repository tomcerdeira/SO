#ifndef LIBC_H
#define LIBC_H

#include <stdint.h>
#include <consoleManager.h>
#include <videoDriver.h>
#include <sysHandler.h>

void *memset(void *destination, int32_t character, uint64_t length);
void *memcpy(void *destination, const void *source, uint64_t length);
int numToStr(char *str, int num);
void printBase(uint64_t value, uint_least32_t base);
void printRegisters(uint64_t *stackFrame);
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);
int BCDtoInt(uint64_t number);
void setReturns(void *ip_, void *sp_);
uint64_t *getIntructionPointer();
uint64_t *getStackPointer();
int strcompare(char *s1, char *s2);

#endif