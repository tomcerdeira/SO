#ifndef VIDEO_DRIVER_C
#define VIDEO_DRIVER_C
#include <font.h>
#include <stdint.h>

int screenWidth();

int screenHeight();
char * calculatePosition(int x, int y);
int getColorOfPixel(int x, int y);

void drawPixel(int x, int y, int color);
void drawFigure(unsigned char * code, int x, int y, int width, int height,int color, int background_color);

void drawLetter(int key, int x, int y, int color, int background_color);
void drawRectangle(int x, int y, int color, int width, int height);

#endif