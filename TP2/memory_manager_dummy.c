#include "includes.h"

#define MEMORY_SIZE 1256

#define BLOCK 8

struct memoryBlock
{
    char *start;
    int cantOfBlocks;
    int isFree; // 0 OCUPADA - 1 LIBRE
};

int indexMemoryAsigned = 0;
struct memoryBlock asignedMemory[10];

char start[MEMORY_SIZE] = {'\0'};

char *next = start; //next siempre apunta a la última posición de memoria que se puede usar

int main(int argc, char *argv[])
{
    char *ptr;
    int i;
    int j = 0;
    ptr = dummy_malloc_with_blocks(5);
    if (ptr == NULL)
    {
        printf("No pude asignar memoria primer caso!\n");
    }
    // for (i = 0; i < 40; i++)
    // {
    //     ptr[i] = 'a' + i;
    // }

    char *ptr2;
    ptr2 = dummy_malloc_with_blocks(5);
    if (ptr2 == NULL)
    {
        printf("No pude asignar memoria segundo caso!\n");
    }
    char *ptr3;
    ptr3 = dummy_malloc_with_blocks(5);
    if (ptr3 == NULL)
    {
        printf("No pude asignar memoria tercer caso!\n");
    }
    char *ptr4;
    ptr4 = dummy_malloc_with_blocks(5);
    if (ptr4 == NULL)
    {
        printf("No pude asignar memoria cuarta caso!\n");
    }
    char *ptr5;
    ptr5 = dummy_malloc_with_blocks(5);
    if (ptr5 == NULL)
    {
        printf("No pude asignar memoria quinto caso!\n");
    }
    char *ptr6;
    ptr6 = dummy_malloc_with_blocks(5);
    if (ptr6 == NULL)
    {
        printf("No pude asignar memoria sexto caso!\n");
    }
    //
    for (i = 0; i < indexMemoryAsigned; i++)
    {
        printf("Is not FREE= %d\n", asignedMemory[i].isFree);
    }
    //
    printf("Ya DI toda la memoria \n");
    printf("Voy a liberar la memoria \n");
    freeMemory(ptr);
    freeMemory(ptr2);
    freeMemory(ptr3);
    ptr3 = dummy_malloc_with_blocks(4);
    freeMemory(ptr4);
    freeMemory(ptr5);
    freeMemory(ptr6);
    //
    for (i = 0; i < indexMemoryAsigned; i++)
    {
        printf("Is FREE= %d\n", asignedMemory[i].isFree);
    }
    //
    printf("Ya LIBERE toda la memoria \n");
    return 0;
}

void *dummy_malloc(int size)
{
    char *r = next;
    if (next - start <= MEMORY_SIZE - size)
    {
        next += size;
        return r;
    }
    else
    {
        return NULL;
    }
}

void *dummy_malloc_with_blocks(int requestedCantOfBlocks)
{
    struct memoryBlock mb;

    mb.cantOfBlocks = requestedCantOfBlocks;

    char *r;
    int t = 0;
    for (; t < indexMemoryAsigned; t++) // Busco una posicion en el arreglo para reutilizar
    {
        if (asignedMemory[t].isFree && asignedMemory[t].cantOfBlocks >= requestedCantOfBlocks)
        {
            printf("Reutilizo un bloque \n");
            mb.start = asignedMemory[t].start;
            asignedMemory[t] = mb;
            asignedMemory[t].isFree = 0;
            r = mb.start;
            return r;
        }
    }

    if (next - mb.start <= MEMORY_SIZE - (mb.cantOfBlocks * BLOCK)) //se fija si entra en la memoria a partir de next
    {
        mb.start = next;
        next += (mb.cantOfBlocks * BLOCK);

        mb.isFree = 0;
        asignedMemory[indexMemoryAsigned++] = mb;
        r = mb.start;

        return r;
    }
    else
    {
        return NULL; //NO encontro espacio liberado NI le entro en el espacio que quedaba en memoria
    }
}

void freeMemory(char *ptr)
{
    int index_of_block = indexOfMemoryBlock(ptr);
    if (index_of_block == -1 || asignedMemory[index_of_block].isFree)
    {
        return;
    }
    asignedMemory[index_of_block].isFree = 1; // Deja el espacio libre para escritura, no la limpia
}

int indexOfMemoryBlock(char *ptr)
{
    int i = 0;

    for (; i < indexMemoryAsigned; i++)
    {
        if (ptr >= asignedMemory[i].start && ptr < (asignedMemory[i].start + (asignedMemory[i].cantOfBlocks * BLOCK)))
        {
            return i;
        }
    }
    return -1;
}