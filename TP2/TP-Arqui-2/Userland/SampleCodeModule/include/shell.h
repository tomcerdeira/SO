#ifndef SHELL_H_USER
#define SHELL_H_USER
#include <libasm.h>
#include <chessPieces.h>
#include <chess.h>
#include <standardLib.h>

#include <exceptionsManager.h>

#define ERROR_COLOR 0xFF0000
#define USER_COLOR 0x1a921c
#define MODULE_COLOR 0xffce03
#define FONT_COLOR 0xFFFFFF

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 764 //ver donde deberia ir

void shellManager();
void init();
// void shell();
// void loadModule(char *module);
void shellHandler();

#endif