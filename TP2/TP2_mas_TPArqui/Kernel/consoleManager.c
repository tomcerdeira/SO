// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "consoleManager.h"

#define BACKGROUND_COLOR 0x000000
#define LETTER_COLOR 0xFFFFFF

#define BACKSPACE_KEY 0x0E

screen_info myScreen = {0, 0, 0xFFFFFF, 0x00};
int isSettedCursor = 0;
int settedX = 0;
int settedY = 0;

void setCursor(uint64_t x, uint64_t y)
{
    settedX = x;
    settedY = y;
    isSettedCursor = 1;
    return;
}
void disableCursor()
{
    isSettedCursor = 0;
}
void initScreen()
{
    int y = screenHeight();
    myScreen.currentY = y - CHAR_HEIGHT; 
}

void print(char *string, int font_color, int background_color)
{
    myScreen.backgroundColor = background_color;
    myScreen.fontColor = font_color;
    int *posX;
    int *posY;
    if (!isSettedCursor)
    {
        posX = &myScreen.currentX;
        posY = &myScreen.currentY;
    }
    else
    {
        posX = &settedX;
        posY = &settedY;
    }

    for (int i = 0; string[i] != 0; i++)
    {
        if (string[i] == '\n' || *posX == screenWidth()) //si se introdujo un \n o se llego al final de la pantalla
        {
            newLine(CHAR_WIDTH, CHAR_HEIGHT, font_color, background_color); //sigue en una nueva linea --> mueve lo anterior para arriba
        }
        else if (string[i] == '\b' || string[i] == DELETE_KEY) //si se borro
        {
            delete ();
        }
        else
        {
            drawLetter(string[i], *posX, *posY, font_color, background_color);
            *posX += CHAR_WIDTH;
        }
    }
    return;
    
}

// Salto de linea
void newLine(int width, int height, int color, int background_color)
{
    int *posX;
    int *posY;

    if (!isSettedCursor)
    {
        posX = &myScreen.currentX;
        posY = &myScreen.currentY;
    }
    else
    {
        posX = &settedX;
        posY = &settedY;
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < screenWidth(); x++)
        {
            drawPixel(x, y, 0x000000);
        }
    }

    for (int y = 0; y < screenHeight() - height; y++)
    {
        for (int x = 0; x < screenWidth(); x++)
        {
            int color = getColorOfPixel(x, y);
            drawPixel(x, y, getColorOfPixel(x, y + height));
            drawPixel(x, y + height, color);
        }
    }
    *posX = 0;
    return;
}

// // Borra el caracter anterior al cursor
void delete ()
{
    int *posX;
    int *posY;
    if (!isSettedCursor)
    {
        posX = &myScreen.currentX;
        posY = &myScreen.currentY;
    }
    else
    {
        posX = &settedX;
        posY = &settedY;
    }
    if (*posX != 0)
    {
        for (int j = 0; j < CHAR_HEIGHT; j++)
        {
            for (int i = 0; i < CHAR_WIDTH; i++)
            {
                drawPixel(*posX - i, *posY + j, myScreen.backgroundColor);
            }
        }

        *posX -= CHAR_WIDTH;
    }
    return;
}

void deleteN(int n)
{
    for (int i = 0; i < n; i++)
    {

        delete ();
    }
}

screen_info getScreenInfo()
{
    return myScreen;
}
void clearConsole()
{
    
    for (int i = 0; i < screenWidth() / 2; i++)
    {
        for (int j = myScreen.currentY; j > 0; j--)
        {
            drawPixel(i, j, 0x000000);
            drawPixel(screenWidth() - i, j, 0x000000);
            
        }
    }
    int y = screenHeight();
    myScreen.currentY = y - CHAR_HEIGHT;
    myScreen.currentX = 0;
}

void clearConsoleIn(int seconds)
{
    print("La pantalla se reiniciara en ", LETTER_COLOR, BACKGROUND_COLOR);
    _hlt();
    int startingTime = getSecondsTimer();
    int aux = seconds;
    int i = seconds;
    char buff[3] = {0};
    uintToBase(aux, buff, 10);
    print(buff, 0xFF0000, BACKGROUND_COLOR);
    while (i > 0)
    {
        _hlt();
        aux = seconds - (getSecondsTimer() - startingTime);
        if (i != aux)
        {
            delete (BACKGROUND_COLOR);
            if (i % 10 == 0) //por si son numero de dos digitos
            {
                delete (BACKGROUND_COLOR);
                delete (BACKGROUND_COLOR);
            }
            i = aux;
            uintToBase(i, buff, 10);
            print(buff, 0xFF0000, BACKGROUND_COLOR);
        }
    }
    newLine(CHAR_WIDTH, CHAR_HEIGHT, LETTER_COLOR, BACKGROUND_COLOR);

    clearConsole();
}

void printFigure(unsigned char *code, int x, int y, int width, int height, int color, int background_color)
{
    int *posX = &myScreen.currentX;
   
    if (*posX == screenWidth()) //si se introdujo un \n o se llego al final de la pantalla
    {
        newLine(width, height, color, background_color); //sigue en una nueva linea --> mueve lo anterior para arriba
    }
    
    drawFigure(code, myScreen.currentX, myScreen.currentY, 8, 16, 0x0000000, 0xFFFFFF);
    *posX += width;
}