#ifndef PIPE
#define PIPE

#include <memory_manager.h>
#include <lib.h>
#include <synchro.h>

#define SIZE_OF_PIPE 2048
#define CANT_OF_PIPES 10

typedef struct
{
    int readIndex;
    int writeIndex;
    char *buffer;
    int fd;
    int isFree;
    int cantOfProcessesConsuming;
    semT * sem;
} pipe;

void initPipes();
int getFreePipe();
void createNewPipe(int *fd);
int getPipeByFD(int fd);
void closePipe(int fd);
void writePipe(int fd, char *buffer);
int readPipe(char *buffer, int size, int fd);
char *getBuffOf(char *buff, int fd);

#endif
