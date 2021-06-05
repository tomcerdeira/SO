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
#include "desafios.h"

#define PORT 8080
#define CANT_DESAFIOS 13
#define CANT_CHARACTER_USED 123

double gauss(void);
int gdbme();
//int createServer(struct sockaddr_in *server);

#endif