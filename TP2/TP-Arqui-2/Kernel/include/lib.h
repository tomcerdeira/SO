#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <registers.h>

char *cpuVendor(char *result);

uint8_t getDay();
uint8_t getMonth();
uint8_t getYear();
uint8_t getHour();
uint8_t getMins();
uint8_t getSeconds();
char readKeyboard();
uint64_t *getMemory(uint64_t init);
uint64_t *getSP();
void snapShotRegister();
void timerTickInterrupt();
int strcmp(char *s1, char *s2);

#endif