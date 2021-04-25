#include "includes.h"

void *mallocPowersOfTwo(int sizeOf)
{
    int i = MEMORY_SIZE;

    for (; i >= 0; i / 2)
    {
        if (sizeOf >= i)
        {
            return mallocNUESTRO(i * 2);
        }
    }
    return NULL; // ERROR!
}