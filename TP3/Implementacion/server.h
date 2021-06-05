#ifndef SERVER_TP
#define SERVER_TP
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>

#define PORT 8080
#define WRITE_EBADF 13
#define CANT_DESAFIOS 13
#define CANT_CHARACTER_USED 123
#define DESAFIO "------------- DESAFIO -------------\n"
#define PREGUNTA "----- PREGUNTA PARA INVESTIGAR -----\n"
#define PI 3.14159265358979323846

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
double gauss(void);
int gdbme();

#endif