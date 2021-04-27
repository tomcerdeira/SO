#ifndef CONSOLE_MANAGER_C
#define CONSOLE_MANAGER_C
#include <videoDriver.h>
#include "font.h"
#include <keyboardDriver.h>
#include <stdint.h>
#include <time.h>
#include <libC.h>
#include <interrupts.h>
#include <timer.h>
#include <lib.h> //borrar

typedef struct
{
    int currentX;
    int currentY;
    int fontColor;
    int backgroundColor;
} screen_info;

void print(char *string, int letter_color, int background_color);
void initScreen();
void newLine(int width, int height, int color, int background_color);
void delete ();
screen_info getScreenInfo();
void clearConsole();
void clearConsoleIn(int seconds);
void printFigure(unsigned char *code, int x, int y, int width, int height, int color, int background_color);
void deleteN(int n);
void disableCursor();
void setCursor(uint64_t x, uint64_t y);
#endif