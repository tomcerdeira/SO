#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int connectToServer(struct sockaddr_in *server);