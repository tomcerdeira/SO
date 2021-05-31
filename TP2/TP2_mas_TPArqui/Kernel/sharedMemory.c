#include <sharedMemory.h>

shared_block sharedBlocks[CANT_BLOCKS_SHARED_MEMORY] = {{0}};


void initSharedMemory(){
    int i=0;
    shared_block aux;
    aux.isFree = FREE;
    aux.ptr = 0;
    aux.size = 0;
    aux.beingUsedBy =0;
    for(;i<CANT_BLOCKS_SHARED_MEMORY;i++){
        sharedBlocks[i]=aux; 
    }    
}

void * shm_open(int index, int size){

    if (index < 0 || index > CANT_BLOCKS_SHARED_MEMORY){
        return 0; // NULL
    }
    
    if(sharedBlocks[index].isFree){
        if (getMemoryAvailable() < size)
        {
            return 0; // NULL //error: no hay sufieciente memoria en el memeory manager
        }
        sharedBlocks[index].ptr = mallocNUESTRO(size);
        sharedBlocks[index].size = size;
        sharedBlocks[index].isFree = NOT_FREE;        
    }
    
    sharedBlocks[index].beingUsedBy++;
    return sharedBlocks[index].ptr;  
}

void shm_close(int index){

    if (index < 0 || index > CANT_BLOCKS_SHARED_MEMORY){
        return -1;
    }
    
    sharedBlocks[index].beingUsedBy--;
    
    if (sharedBlocks[index].beingUsedBy == 0){
        sharedBlocks[index].isFree = FREE;
        sharedBlocks[index].size = 0;
        freeMemory(sharedBlocks[index].ptr);
        sharedBlocks[index].ptr = 0;
    }
}