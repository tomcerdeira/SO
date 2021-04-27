#ifndef KEYBOARD_H
#define KEYBOARD_H

#define BUFFER_SIZE 20

#include <lib.h>
#include <libC.h>
#include <stdint.h>
#include <consoleManager.h>
#include <registers.h>

#define KEYS 59
#define ESC 0x1B
#define DELETE_KEY 0x0E
#define DELETE_KEY_RELEASED 0xFFFFFFFFFFFFFF8E

#define R_HEXA_CODE 0x13

#define L_SHIFT 0x2A
#define R_SHIFT 0x36
#define CAPS_LCK 0x3A
#define CTRL 0x1D
#define ESC 0x1B
#define ESPACE 0x39
#define ERROR -1
#define R_SHIFT_RELEASED 0xFFFFFFFFFFFFFFB6
#define L_SHIFT_RELEASED 0xFFFFFFFFFFFFFFAA
#define PRESSED 1
void checkBuffer();
void readKeyboardBuffer();
char *getKeyboardBuffer();
void cleanBuffer();

#endif