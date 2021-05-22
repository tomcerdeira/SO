#include <memory_manager.h>

int indexMemoryAsigned = 0;
memoryBlock bitMapMemory[CANTBLOCKS];
int id = 0;

int cantOfMemoryUsed = 0;

static char *const start = (void *)0x600000; //

char *next = &start; 
// Inicializamos el bitMap
void initializeMemory()
{
    int i = 0;
    for (; i < CANTBLOCKS; i++)
    {
        memoryBlock newMemoryblock;
        newMemoryblock.cantOfBlocks = 1;
        newMemoryblock.isFree = 1;
        newMemoryblock.start = (start + i * BLOCK);
        newMemoryblock.id_request = id;
        bitMapMemory[i] = newMemoryblock;
    }
}

void *dummy_malloc_with_blocks(int requestedCantOfBlocks)
{
    int i = 0;

    int index = searchFreeBlocks(requestedCantOfBlocks);

    

    if (index >= 0)
    {
        i = index;
        id += 1;
        for (; i < index + requestedCantOfBlocks; i++)
        {
            bitMapMemory[i].isFree = 0;
            bitMapMemory[i].id_request = id;
            cantOfMemoryUsed++;
        }
        return bitMapMemory[index].start;
    }
    // Si llega aca es por que no hay memoria contigua libre para dar
    return NULL;
}

int searchFreeBlocks(int requestedBlocks)
{
    int i = 0;
    int flag = 1;
    for (; i < CANTBLOCKS; i++)
    {
        if (bitMapMemory[i].isFree == 1)
        {
            
            int j = i + 1;
            for (; j < CANTBLOCKS && flag && j < i + requestedBlocks; j++)
            {
                
                if (!bitMapMemory[j].isFree)
                {
                    flag = 0;
                }
            }
            if (flag)
            {
                return i;
            }
            else
            {
                flag = 1;
                i = j;
            }
        }
    }
    return -1;
}

int searchIndexBitMap(char *ptr)
{
    int i = 0;

    for (; i < CANTBLOCKS; i++)
    {
        if (ptr >= bitMapMemory[i].start && ptr < (bitMapMemory[i].start + BLOCK))
        {
            return i;
        }
    }
    return -1;
}

void freeMemory(char *ptr)
{
    int index_block = searchIndexBitMap(ptr);
    if (index_block < 0)
    {
        
        return;
    }
    int id_find = bitMapMemory[index_block].id_request;

    int t = index_block;

    while (bitMapMemory[t].id_request == id_find && t >= 0)
    {
        bitMapMemory[t].isFree = 1;
        t--;
        cantOfMemoryUsed--;
    }

    t = index_block + 1;
    while (bitMapMemory[t].id_request == id_find && t <= CANTBLOCKS)
    {
        bitMapMemory[t].isFree = 1;
        t++;
        cantOfMemoryUsed--;
    }
}

void *mallocNUESTRO(int size)
{
    int cantBlocks = size / BLOCK + 1;
    return dummy_malloc_with_blocks(cantBlocks);
}

void *memsetNUESTRO(char *ptr, int toWrite, int size)
{

    int index = searchIndexBitMap(ptr);
    int id_found = bitMapMemory[index].id_request;
    int i = index;
    int j = 0;

    while (bitMapMemory[i].id_request == id_found && size != 0)
    {
        for (; j < BLOCK && size != 0; j++)
        {
            
            bitMapMemory[i].start[j] = toWrite;
            size--;
        }
        i++;
        j = 0;
    }

    if (size == 0)
    {
        return bitMapMemory[index].start;
    }

    return NULL;
}

int getTotalMemorySize()
{
    return MEMORY_SIZE;
}

int getMemoryAvailable()
{
    return MEMORY_SIZE - (cantOfMemoryUsed * BLOCK);
}

int getMemoryUsed()
{
    return (cantOfMemoryUsed * BLOCK);
}

void getMemoryInfo(char *buffer)
{
    int i = 0;
    int j = 0;

    char *header = "Total\t\tEn uso\tLibre\n";

    memcpy(buffer, header, strlen(header));
    j = strlen(header);

            //Total
            char auxTotal[6];
            numToStr(auxTotal, getTotalMemorySize());
            memcpy(buffer + j, auxTotal, strlen(auxTotal));
            j += strlen(auxTotal);
            memcpy(buffer + j, "\t\t\t", strlen("t\t\t"));
            j += strlen("\t\t\t");

            //En uso
            char auxUsed[2];
            numToStr(auxUsed, getMemoryUsed());
            memcpy(buffer + j, auxUsed, strlen(auxUsed));
            j += strlen(auxUsed);
            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

            //Libre
            char auxFree[6];
            numToStr(auxFree, getMemoryAvailable());
            memcpy(buffer + j, auxFree, strlen(auxFree));
            j += strlen(auxFree);

            memcpy(buffer + j, "\n", strlen("\n"));
            j += strlen("\n");
        
    
}
