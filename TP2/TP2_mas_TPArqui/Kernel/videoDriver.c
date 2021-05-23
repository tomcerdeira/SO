// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include "videoDriver.h"
#include "font.h"
struct vbe_mode_info_structure
{
	uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;	  // deprecated
	uint8_t window_b;	  // deprecated
	uint16_t granularity; // deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;		   // number of bytes per horizontal line
	uint16_t width;		   // width in pixels
	uint16_t height;	   // height in pixels
	uint8_t w_char;		   // unused...
	uint8_t y_char;		   // ...
	uint8_t planes;
	uint8_t bpp;   // bits per pixel in this mode
	uint8_t banks; // deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__((packed));

struct vbe_mode_info_structure *screenData = (struct vbe_mode_info_structure *)0x0000000000005C00;

int screenWidth()
{
	return screenData->width; // width en pixeles
}

int screenHeight()
{
	return screenData->height; //height en pixeles
}

// Retorna una puntero a char de la posicion en pantalla a escribir
char *calculatePosition(int x, int y)
{
	return (char *)(screenData->framebuffer + (x + screenData->width * y) * 3);
}

void drawPixel(int x, int y, int color)
{
	char *curpos = calculatePosition(x, y);

	int b = color & 0x0000FF;
	int g = (color >> 8) & 0x0000FF;
	int r = (color >> 16) & 0x0000FF;

	*curpos = b;
	curpos++;
	*curpos = g;
	curpos++;
	*curpos = r;
}

// // retorna el color (en formato hexadecimal) de dicho pixel
int getColorOfPixel(int x, int y)
{
	char *pos = calculatePosition(x, y);
	return ((pos[2] & 0xff) << 16) + ((pos[1] & 0xff) << 8) + (pos[0] & 0xff);
	//return curpos[0] + (curpos[1] << 8) + (curpos[2] << 16);
}

void drawFigure(unsigned char *code, int x, int y, int width, int height, int color, int background_color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((code[j] >> (width - i)) & 0x01)
			{
				// drawRectangle(x + i, y + j, color, 20, 20);
				// drawRectangle(100, 100, color, 20, 20);
				drawPixel(x + i, j + y, color);
			}
			else
			{
				//	drawRectangle(x + i, y + j, background_color, 1, 1);
				drawPixel(x + i, j + y, background_color);
			}
		}
	}

	// for (int i = 0; i < width + height; i++)
	// {
	// 	int auxW = (i - height) % width;
	// 	int auxH = (i - width) % height;
	// 	drawLetter(code[i], x + auxW, y + auxH, color, background_color);
	// }
}
#include <libC.h>
void drawRectangle(int x, int y, int color, int width, int height)
{

	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			drawPixel(i, j, color);
		}
	}
}

void drawLetter(int key, int x, int y, int color, int background_color)
{
	//char * curpos = calculatePosition(x, y);
	unsigned char *letter = charBitmap(key);
	//drawFigure(charBitmap(key), x, y, 8, 16, color, background_color);
	for (int i = 0; i < CHAR_WIDTH; i++)
	{
		for (int j = 0; j < CHAR_HEIGHT; j++)
		{
			if ((letter[j] >> (CHAR_WIDTH - i)) & 0x01)
			{
				drawPixel(x + i, j + y, color);
			}
			else
			{
				drawPixel(x + i, j + y, background_color);
			}
		}
	}
}
