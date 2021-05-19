#ifndef PIPE
#define PIPE

#include <memory_manager.h>
#include <lib.h>

#define SIZE_OF_PIPE 1024
#define CANT_OF_PIPES 10

typedef struct
{
    int readIndex;
    int writeIndex;
    char *buffer;
    int fd;
    int isFree;
    int cantOfProcessesConsuming;
} pipe;

void initPipes();
int getFreePipe();
void createNewPipe(int *fd);
int getPipeByFD(int fd);
void closePipe(int fd);
void writePipe(int fd, char *buffer);
int readPipe(char *buffer, int size, int fd);

#endif
