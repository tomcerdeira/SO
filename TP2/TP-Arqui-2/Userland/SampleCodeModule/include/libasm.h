#ifndef LIBASM_USER
#define LIBASM_USER
#include <stdint.h>
void write(char *buffer, int fontColor, int fd);
void readKeyBuff(char *buffer, int longBuffer, int fd);
void getTime(uint8_t *buffer, int parameter);
void getRegisterState(int *buffer);
void getMemoryState(unsigned char *buffer, int memoryStart);

void printFigure(uint64_t *code, int width, int height, uint64_t *colors, uint64_t *pos);
void deleteN(int n); /// Borra desde dond eesta el cursor n para atras.
void clearConsoleIn(int seconds);
void getSecondsCronometro(uint64_t *seconds);
void setCronometro(int activate);
void disableCursor();

void setCursorUser(uint64_t x, uint64_t y);
void printRectangle(uint64_t *pos, int color, uint64_t *widthHeight);

int createP(char *name, void *func, int argc, char *argv[]);
int getProcessPid();
void halt();
void block(int pid);
void nice(int pid, int newTimeSlot);
void ps(char *buf);
void test_sync();
void test_no_sync();
void test_processes();
void kill(int pid);


int getPipe(int *fd);

void changeOutputFd(int pid, int fd);
void changeInputFd(int pid, int fd);
void getPidByName(char *name, int *fd);

#endif