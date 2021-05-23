// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "text_driver.h"

char *screen_start = (char *)0xB8000;

void hello_world()
{
    char *mensaje = "Hello World!";

    while (*mensaje != "\0")
    {
        *screen_start = *mensaje;
        screen_start += 2;
        mensaje++;
    }
}