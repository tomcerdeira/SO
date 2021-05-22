#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

// #include <stdlib.h>
// #include <stdio.h>
// #include <pthread.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// // #include <errno.h>
// #include <sys/select.h>
// #include <limits.h>
// #include <sys/mman.h>
// #include <semaphore.h>
// #include <math.h>
#include <stdint.h>
// #define NULL 0

#define MEMORY_SIZE 4096 * 20
#define BLOCK 8
#define CANTBLOCKS (int)MEMORY_SIZE / BLOCK

void *dummy_malloc(int size);
void *dummy_malloc_with_blocks(int requestedCantOfBlocks);
void freeMemory(char *ptr);
int indexOfMemoryBlock(char *ptr);
int searchFreeBlocks(int requestedBlocks);
void initializeMemory();
void *mallocNUESTRO(int size);
void *memsetNUESTRO(char *ptr, int toWrite, int size);
int getMemoryAvailable();
int getMemoryUsed();
int getTotalMemorySize();
void getMemoryInfo(char * buffer);

typedef struct
{
    char *start;
    int cantOfBlocks;
    int isFree; // 0 OCUPADA - 1 LIBRE
    int id_request;
} memoryBlock;

#endif