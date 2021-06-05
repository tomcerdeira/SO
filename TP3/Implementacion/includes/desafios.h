#ifndef DESAFIOS_H
#define DESAFIOS_H
#include <stdio.h>
#include <string.h> //strlen
#include <unistd.h> //write
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>

#define WRITE_EBADF 13
#define CANT_DESAFIOS 13
#define CANT_CHARACTER_USED 123
#define DESAFIO "------------- DESAFIO -------------\n"
#define PREGUNTA "----- PREGUNTA PARA INVESTIGAR -----\n"
#define PI 3.14159265358979323846
#define ASCII_NO_REPRESENTABLES 32 // https://elcodigoascii.com.ar/
#define BLACK_COLOR_PRINTF "\033[0;30m"
#define RESET_COLOR "\033[0m"

int compare(char *str1, char *str2);
void desafio1();
void desafio2();
void desafio3();
void desafio4();
void desafio5();
void desafio6();
void desafio7();
void desafio8();
void desafio9();
void desafio10();
void desafio11();
void desafio12();
void finDesafios();
#endif