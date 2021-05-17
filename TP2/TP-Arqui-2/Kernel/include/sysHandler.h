#ifndef SYS_HANDLER_H
#define SYS_HANDLER_H
#include <stdint.h>
#include <keyboardDriver.h>
#include <lib.h>
#include <consoleManager.h>
#include <videoDriver.h>
#include <libC.h>
#include <registers.h>
#include <time.h>
#include <scheduler.h>
#include <test_sync.h>

#define MEMORY_REQUIRED 32
// Tomamos como modelo las de linux
// uint64_t es un tipo de dato que "It turns out that they are equal respectively to: unsigned char, unsigned short, unsigned int and unsigned long long. "
//ssize_t read(int fd, void *buf, size_t count)
//ssize_t write(int fd, const void *buf, size_t count)
//fd – file descriptor
//buf – pointer to the buffer to fill with read contents
//count – number of bytes to read/write
//par1 --> RD1
//par2 --> RSI
//par3 --> RDX
//sysCallDescryptor --> R10

void sysHandler(uint64_t *par1, uint64_t par2, uint64_t par3, int sysCallID, uint64_t *stackFrame, uint64_t *par5, uint64_t *par6);
void writeScreen(uint64_t *buffer, uint64_t fontColor, uint64_t background_color);
void read(uint64_t *buffer, uint64_t lengthBuffer);
void getDecimalTime(uint8_t *buff, uint64_t fd);
void sysGetRegisterState(uint64_t *par1, uint64_t *stackFrame);
void getMemoryState(unsigned char par1[], uint64_t memoryStart);
// void clearConsoleIn(int seconds);

#endif
