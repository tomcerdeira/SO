#include <includes.h>


typedef struct 
{
    memoryBlock block;
    node * next;
}node;


typedef struct
{
    int size;
    node * first;
}headLinkedList;


headLinkedList creatList()
{
    return dummy_malloc_with_blocks(())
}
