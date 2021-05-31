#ifndef SHARED_MEMORY
#define SHARED_MEMORY
#define CANT_BLOCKS_SHARED_MEMORY 10
#define FREE 1
#define NOT_FREE 0


#include <memory_manager.h>
#include <libC.h>


typedef struct{
    char * name;
    int size;
    int isFree;
    uint64_t * ptr;
    int beingUsedBy;
}shared_block;

void initSharedMemory();
void * shm_open(int index, int size);
void shm_close(int index);


#endif