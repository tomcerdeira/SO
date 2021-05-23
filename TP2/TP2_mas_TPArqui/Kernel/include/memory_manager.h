#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include <stdint.h>
#include <libC.h>

#define MEMORY_SIZE 4096 * 20
#define BLOCK 8
#define MAX_BLOCKS (int)MEMORY_SIZE / BLOCK

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
void getMemoryInfo(char *buffer);

typedef struct
{
    char *start;
    int cantOfBlocks;
    int isFree; // 0 OCUPADA - 1 LIBRE
    int id_request;
} memoryBlock;

#endif