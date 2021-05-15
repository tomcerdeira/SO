#ifndef LIBASM_USER
#define LIBASM_USER
#include <stdint.h>
void writeScreen(char *buffer, int fontColor, int backgrounColor);
void readKeyBuff(char *buffer, int longBuffer);
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
void ps(char * buf);

#endif